#include <jni.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iosfwd>
#include "common/MathFun.h"
#include "common/LogFun.h"
#define TAG "NativeRenderJni"

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL
Java_com_scott_nativecode_NativeRenderJni_onSurfaceCreated(JNIEnv *env, jobject thiz) {
    LOGI(TAG,"native onSurfaceCreated");
}

JNIEXPORT void JNICALL
Java_com_scott_nativecode_NativeRenderJni_onSurfaceChanged(JNIEnv *env, jobject thiz, jint width,
                                                           jint height) {
    LOGI(TAG,"native onSurfaceChanged");

}
JNIEXPORT void JNICALL
Java_com_scott_nativecode_NativeRenderJni_onDrawFrame(JNIEnv *env, jobject thiz) {
    LOGI(TAG,"native onDrawFrame");

}
JNIEXPORT void JNICALL
Java_com_scott_nativecode_NativeRenderJni_init(JNIEnv *env, jobject thiz) {

}



#ifdef __cplusplus
}
#endif
