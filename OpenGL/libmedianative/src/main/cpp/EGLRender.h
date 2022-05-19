//
// Created by 孙全 on 2022/5/15.
//

#ifndef OPENGL_EGLRENDER_H
#define OPENGL_EGLRENDER_H
#pragma once
#include <string>
#include "common/TypeUtil.h"
#include "common/LogFun.h"
#include "common/AssetFun.h"
#include <GLES3/gl3.h>
#include "common/GLUtils.h"

using namespace std;


class EGLRender {
public:
    EGLRender();
    ~EGLRender();
    void onInit(JNIEnv *env,jobject asset_manager,const string &vertexShaderAssetName,const string &fragmentShaderAssetName);
    void onDraw();
    void onSurfaceCreated();
    void onSurfaceChange(int width,int height);
    void onDestroy();

    static EGLRender *getInstance();

private:
    static EGLRender *m_Instance;

protected:
    /**
     * 程序对象
     */
    GLuint m_ProgramObj;

    /**
     * 顶点着色器
     */
    const char *VERTEX_SHADER;
    /**
     * 片段着色器脚本
     */
    const char *FRAGMENT_SHADER;
    /**
     * 屏幕宽度
     */
    int m_Width;
    /**
     * 屏幕高度
     */
    int m_Height;

};


#endif //OPENGL_EGLRENDER_H
