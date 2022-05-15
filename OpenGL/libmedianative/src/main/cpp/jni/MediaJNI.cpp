#include <jni.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iosfwd>
#include "common/JavaClassPath.h"
#include "common/MathFun.h"
#include "common/LogFun.h"
#define TAG "MediaJni"


#ifdef __cplusplus
extern "C" {
#endif
const JNINativeMethod methods_camera_glsurfaceview[] = {
};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *) {
    JNIEnv *env = NULL;
    jclass clazz = NULL;
    jint result = JNI_OK;

    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        LOGE(TAG,"JNI_OnLoad error");
        return JNI_ERR;
    }
    //mediaSDK
    clazz = env->FindClass(PATH_JAVA_CAMERAGL_SURFACEVIEW);
    if (clazz != NULL){
        result = env->RegisterNatives(clazz, methods_camera_glsurfaceview, ARRLEN(methods_camera_glsurfaceview));
    }

    if(result != JNI_OK){
        LOGE(TAG,"JNI_OnLoad RegisterNatives error");
        return JNI_ERR;
    }
    return JNI_VERSION_1_4;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *) {
    JNIEnv *env = NULL;
    jclass clazz = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        LOGE(TAG,"JNI_OnUnload error");
        return;
    }
    clazz = env->FindClass(PATH_JAVA_CAMERAGL_SURFACEVIEW);
    if(clazz != NULL){
        env->UnregisterNatives(clazz);
    }
}

#ifdef __cplusplus
}
#endif