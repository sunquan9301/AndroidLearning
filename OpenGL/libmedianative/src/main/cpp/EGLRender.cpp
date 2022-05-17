//
// Created by 孙全 on 2022/5/15.
//

#include "EGLRender.h"

EGLRender *EGLRender::m_Instance = new EGLRender();


EGLRender *EGLRender::getInstance() {
    return m_Instance;
}


EGLRender::EGLRender() {
}

EGLRender::~EGLRender() = default;


void EGLRender::onDraw() {

}

void EGLRender::onSurfaceChange(int width, int height) {

}

void EGLRender::onDestroy() {

}

void EGLRender::onInit(JNIEnv *env, jobject asset_manager, const string &vertexShaderAssetName,
                       const string &fragmentShaderAssetName) {

    this->fragmentShaderAssetName = fragmentShaderAssetName;
    this->vertexShaderAssetName = vertexShaderAssetName;
    LOGI(TAG_EGL_RENDER,"vertexShaderAssetName = %s, fragmentShaderAssetName = %s",vertexShaderAssetName.c_str(),fragmentShaderAssetName.c_str());
    AAssetManager *pManager = AAssetManager_fromJava(env, asset_manager);
    char *file = AssetFun::readAssetFile(this->vertexShaderAssetName.c_str(), pManager);
    LOGI(TAG_EGL_RENDER,"vertexShaderContent = %s",file);
}

