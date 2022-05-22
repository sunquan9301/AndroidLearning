//
// Created by 孙全 on 2022/5/19.
//

#pragma once

#include <string>
#include "common/TypeUtil.h"
#include "common/LogFun.h"
#include "common/AssetFun.h"
#include <GLES3/gl3.h>
#include "common/GLUtils.h"
class GLAbsRenderV2 {
public:
    GLuint DEFAULT_POS_LOCATION = 0;
    GLAbsRenderV2() {
//        VERTEX_SHADER = GL_NONE;
//        FRAGMENT_SHADER = GL_NONE;
//        m_ProgramObj = 0;
//        m_Width = 0;
//        m_Height = 0;
    }
    virtual ~GLAbsRenderV2() {}
    virtual void onInit(JNIEnv *env,jobject asset_manager) {
        GLUtils::printGLInfo();
//        LOGI(TAG_ABS_RENDER_V2,"vertexShaderAssetName = %s, fragmentShaderAssetName = %s",vertexShaderAssetName.c_str(),fragmentShaderAssetName.c_str());
//        AAssetManager *pManager = AAssetManager_fromJava(env, asset_manager);
//        this->VERTEX_SHADER = AssetFun::readAssetFile(vertexShaderAssetName.c_str(), pManager);
//        this->FRAGMENT_SHADER = AssetFun::readAssetFile(fragmentShaderAssetName.c_str(), pManager);
//        LOGI(TAG_RENDER_TRIANGLE,"vertexShaderContent = %s",this->VERTEX_SHADER);
//        LOGI(TAG_RENDER_TRIANGLE,"fragmentShaderContent = %s",this->FRAGMENT_SHADER);
    }
    virtual void onDraw() = 0;
    virtual void onSurfaceCreated() = 0;
    virtual void onSurfaceChange(int width,int height){
//        LOGI(TAG_ABS_RENDER,"onSurfaceChange, width = %d, height = %d",width,height);
//        this->m_Width = width;
//        this->m_Height = height;
//        glViewport(0,0,width,height);
    }
    virtual void onDestroy(){
//        LOGI(TAG_ABS_RENDER,"onDestroy");
//        if (m_ProgramObj) {
//            glDeleteProgram(m_ProgramObj);
//            m_ProgramObj = GL_NONE;
//        }
//        if(VERTEX_SHADER != nullptr){
//            delete[] VERTEX_SHADER;
//            VERTEX_SHADER = nullptr;
//        }
//        if(FRAGMENT_SHADER!= nullptr){
//            delete[] FRAGMENT_SHADER;
//            FRAGMENT_SHADER = nullptr;
//        }
    }

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


