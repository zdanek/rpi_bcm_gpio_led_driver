#include <stdio.h>
#include "ShiftRegDriver.h"

JNIEXPORT void JNICALL Java_ShiftRegDriver_shiftOut
  (JNIEnv *env, jobject obj, jbyteArray arr, jint arrLength) {

    int i;
    jboolean isCopy;
    jbyte* b = (*env)->GetByteArrayElements(env, arr, &isCopy);

    printf("Hello JNI!\n");
    printf("Array args\n");

    for (i = 0; i < arrLength; i++) {
        printf("%d\n", b[i]);
    }

    (*env)->ReleaseByteArrayElements(env, arr, b, 0);

    //GPIO Stuff

}


int main() {
    printf("This is BCM Shiftreg driver.\n");
}
