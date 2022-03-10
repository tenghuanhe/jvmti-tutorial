#include <stdio.h>
#include <stdlib.h>

#include "jvmti.h"

static void check_jvmti_errors(jvmtiEnv* jvmti, jvmtiError errnum,
                               const char* errmsg) {
  if (errnum != JVMTI_ERROR_NONE) {
    char* errnum_str;
    errnum_str = NULL;
    (void)(*jvmti)->GetErrorName(jvmti, errnum, &errnum_str);
    printf("ERROR: JVMTI: [%d] %s - %s\n", errnum,
           (errnum_str == NULL ? "Unknown" : errnum_str),
           (errmsg == NULL ? "" : errmsg));
  }
}

static void JNICALL callbackMethodEntry(jvmtiEnv* jvmti, JNIEnv* jni,
                                        jthread thread, jmethodID method) {
  char* name_ptr;
  char* signature_ptr;
  char* generic_ptr;
  jvmtiError err;

  err = (*jvmti)->GetMethodName(jvmti, method, &name_ptr, &signature_ptr,
                                &generic_ptr);
  check_jvmti_errors(jvmti, err, "Unable to get the method name.");
  printf("Entered method %s %s\n", signature_ptr, name_ptr);
}

JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM* jvm, char* options,
                                    void* reserved) {
  jvmtiEnv* jvmti;
  jvmtiError err;
  jint res;
  jvmtiEventCallbacks callbacks;
  jvmtiCapabilities capa;
  jrawMonitorID rawMonitorID;

  res = (*jvm)->GetEnv(jvm, (void **)&jvmti, JVMTI_VERSION_1_0);

  if (res != JNI_OK || jvmti == NULL) {
    printf("Unable to get access to JVMTI verson 1.0.\n");
  }

  (void)memset(&capa, 0, sizeof(jvmtiCapabilities));
  capa.can_generate_method_entry_events = 1;
  err = (*jvmti)->AddCapabilities(jvmti, &capa);
  check_jvmti_errors(jvmti, err, "Unable to add the required capabilites.");

  err = (*jvmti)->SetEventNotificationMode(
      jvmti, JVMTI_ENABLE, JVMTI_EVENT_METHOD_ENTRY, (jthread)NULL);
  check_jvmti_errors(jvmti, err, "Unable to set the event notification mode.");

  (void)memset(&callbacks, 0, sizeof(callbacks));
  callbacks.MethodEntry = &callbackMethodEntry;
  err = (*jvmti)->SetEventCallbacks(jvmti, &callbacks, (jint)sizeof(callbacks));
  check_jvmti_errors(jvmti, err, "Unable to set event callbacks.");

  err = (*jvmti)->CreateRawMonitor(jvmti, "JVMTI agent data", &rawMonitorID);
  check_jvmti_errors(jvmti, err, "Unable to create a Raw monitor.");

  return JNI_OK;
}
