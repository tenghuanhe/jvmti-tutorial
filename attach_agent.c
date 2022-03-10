#include <stdio.h>
#include <stdlib.h>

#include "jvmti.h"

JNIEXPORT jint JNICALL Agent_OnAttach(JavaVM* jvm, char* options,
                                      void* reserved) {
  jvmtiEnv* jvmti;
  jvmtiError error;
  jint res;
  jint class_count;
  jclass* classes;
  int i;
  char* signature;

  res = (*jvm)->GetEnv(jvm, (void **) &jvmti, JVMTI_VERSION_1_0);
  if (res != JNI_OK || jvmti == NULL) {
    printf("Unable to get access to JVMTI verson 1.0\n");
  }

  error = (*jvmti)->GetLoadedClasses(jvmti, &class_count, &classes);
  if (error) {
    printf("ERROR: JVMTI GetLoadedClasses failed!\n");
  }

  for (i = 0; i < class_count; i++) {
    (*jvmti)->GetClassSignature(jvmti, classes[i], &signature, NULL);
    printf("class signature=%s\n", signature);
  }

  return JNI_OK;
}
