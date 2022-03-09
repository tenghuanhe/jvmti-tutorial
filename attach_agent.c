#include <stdio.h>
#include <stdlib.h>

#include "jvmti.h"

JNIEXPORT jint JNICALL Agent_OnAttach(JavaVM* jvm, char* options,
                                      void* reserved) {
  jvmtiEnv* jvmti;
  jvmtiError error;
  jint res;
  int i;
  jclass* classes;
  jint count = 0;
  char* signature;

  res = (*jvm)->GetEnv(jvm, (void**)&jvmti, JVMTI_VERSION_1_0);
  if (res != JNI_OK || jvmti == NULL) {
    printf("Unable to get access to JVMTI verson 1.0");
  }

  error = (*jvmti)->GetLoadedClasses(jvmti, &count, &classes);
  if (error) {
    printf("ERROR: JVMTI GetLoadedClasses failed!\n");
  }

  for (i = 0; i < count; i++) {
    (*jvmti)->GetClassSignature(jvmti, classes[i], &signature, NULL);
    printf("class signature=%s\n", signature);
  }

  return error;
}
