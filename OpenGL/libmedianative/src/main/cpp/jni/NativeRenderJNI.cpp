#include <jni.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iosfwd>
#include "common/MathFun.h"
#include "common/LogFun.h"
#include "common/TypeUtil.h"
#include "EGLRender.h"

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
Java_com_scott_nativecode_NativeRenderJni_init(JNIEnv *env, jobject thiz, jobject asset_manager,
                                               jstring vertex_shader_asset_name,
                                               jstring fragment_shader_asset_name) {
    // TODO: implement init()
    EGLRender::getInstance()->onInit(env,asset_manager,JNI_GetString(env,vertex_shader_asset_name),JNI_GetString(env,fragment_shader_asset_name));
}
#ifdef __cplusplus
}
#endif


