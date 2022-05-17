//
// Created by 孙全 on 2022/5/15.
//

#ifndef OPENGL_EGLRENDER_H
#define OPENGL_EGLRENDER_H
#include <string>
#include "common/TypeUtil.h"
#include "common/LogFun.h"
#include "common/AssetFun.h"
using namespace std;


class EGLRender {
public:
    EGLRender();
    ~EGLRender();
    void onInit(JNIEnv *env,jobject asset_manager,const string &vertexShaderAssetName,const string &fragmentShaderAssetName);
    void onDraw();
    void onSurfaceChange(int width,int height);
    void onDestroy();

    static EGLRender *getInstance();

private:
    static EGLRender *m_Instance;
    string vertexShaderAssetName;
    string fragmentShaderAssetName;
};


#endif //OPENGL_EGLRENDER_H
