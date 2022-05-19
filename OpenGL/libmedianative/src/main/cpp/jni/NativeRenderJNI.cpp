#include <jni.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iosfwd>
#include "common/MathFun.h"
#include "common/LogFun.h"
#include "common/TypeUtil.h"
#include "EGLRender.h"


#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL
Java_com_scott_nativecode_NativeRenderJni_onSurfaceCreated(JNIEnv *env, jobject thiz) {
    LOGI(TAG_RENDER_JNI,"native onSurfaceCreated");
    EGLRender::getInstance()->onSurfaceCreated();

}

JNIEXPORT void JNICALL
Java_com_scott_nativecode_NativeRenderJni_onSurfaceChanged(JNIEnv *env, jobject thiz, jint width,
                                                           jint height) {
    EGLRender::getInstance()->onSurfaceChange(width,height);
}
JNIEXPORT void JNICALL
Java_com_scott_nativecode_NativeRenderJni_onDrawFrame(JNIEnv *env, jobject thiz) {
    LOGI(TAG_RENDER_JNI,"native onDrawFrame");
    EGLRender::getInstance()->onDraw();

}

JNIEXPORT void JNICALL
Java_com_scott_nativecode_NativeRenderJni_init(JNIEnv *env, jobject thiz, jobject asset_manager,
                                               jstring vertex_shader_asset_name,
                                               jstring fragment_shader_asset_name) {
    // TODO: implement init()
    EGLRender::getInstance()->onInit(env,asset_manager,JNI_GetString(env,vertex_shader_asset_name),JNI_GetString(env,fragment_shader_asset_name));
}

JNIEXPORT void JNICALL
Java_com_scott_nativecode_NativeRenderJni_onDestroy(JNIEnv *env, jobject thiz) {
    // TODO: implement onDestroy()
    EGLRender::getInstance()->onDestroy();
}

#ifdef __cplusplus
}
#endif


