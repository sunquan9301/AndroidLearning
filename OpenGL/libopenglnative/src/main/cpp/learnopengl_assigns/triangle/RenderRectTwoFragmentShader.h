//
// Created by 孙全 on 2022/5/20.
//

#pragma once
#ifndef OPENGL_RENDERRECTTWOFRAGMENTSHADER_H
#define OPENGL_RENDERRECTTWOFRAGMENTSHADER_H
#include "learnopengl_assigns/GLAbsRender.h"

//使用2个fragment shader，2个VBO, 2个VAO 画不同颜色的2个三角形
class RenderRectTwoFragmentShader : public GLAbsRender{
public:
    virtual void onDraw();
    virtual void onSurfaceCreated();
    virtual void onInit(JNIEnv *env,jobject asset_manager,const string &vertexShaderAssetName,const string &fragmentShaderAssetName);
    virtual void onDestroy(){
        GLAbsRender::onDestroy();
        if (m_ProgramObjGreen) {
            glDeleteProgram(m_ProgramObjGreen);
            m_ProgramObjGreen = GL_NONE;
        }
        if (m_ProgramObjRED) {
            glDeleteProgram(m_ProgramObjRED);
            m_ProgramObjRED = GL_NONE;
        }
        if(FRAGMENT_SHADER_GREEN != nullptr){
            delete[] FRAGMENT_SHADER_GREEN;
            FRAGMENT_SHADER_GREEN = nullptr;
        }
        if(FRAGMENT_SHADER_RED!= nullptr){
            delete[] FRAGMENT_SHADER_RED;
            FRAGMENT_SHADER_RED = nullptr;
        }
    }
private:
    const char * FRAGMENT_SHADER_GREEN;
    const char * FRAGMENT_SHADER_RED; /**
     * 程序对象
     */
    GLuint m_ProgramObjGreen;
    GLuint m_ProgramObjRED;
    GLuint VBOs[2],VAOs[2];
};


#endif //OPENGL_RENDERRECTTWOFRAGMENTSHADER_H
