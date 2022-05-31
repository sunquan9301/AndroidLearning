//
// Created by 孙全 on 2022/5/18.
//
#include <cstdlib>
#include "GLUtils.h"

GLuint GLUtils::createProgram(const char **vertexSource, const char **fragmentSource) {
    GLuint vertexShader = loaderShader(GL_VERTEX_SHADER, vertexSource);
    if(vertexShader == 0){
        return GL_RESULT_ERROR;
    }
    GLuint fragmentShader = loaderShader(GL_FRAGMENT_SHADER, fragmentSource);
    if(fragmentShader == 0){
        return GL_RESULT_ERROR;
    }

    GLuint programId;
    programId = glCreateProgram();
    if(programId == 0){
        LOGE(TAG_GLUTILS,"create program error");
        return GL_RESULT_ERROR;
    }
    glAttachShader(programId,vertexShader);
    checkGlError("AttachVertexShader");
    glAttachShader(programId,fragmentShader);
    checkGlError("AttachFragmentShader");
    glLinkProgram(programId);
    GLint linkStatus;
    glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
    if(linkStatus == GL_FALSE){
        GLint infoLen = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char *infoLog = (char *) malloc(sizeof(char) * infoLen);
            if (infoLog) {
                //获取信息
                glGetProgramInfoLog(programId, infoLen, nullptr, infoLog);
                LOGE(TAG_GLUTILS,"GLUtils::createProgram error linking program:\n%s\n", infoLog);
                free(infoLog);
            }
        }
        // 删除程序对象
        glDeleteProgram(programId);
        return GL_RESULT_ERROR;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return programId;
}

GLuint GLUtils::loaderShader(GLenum type, const char **source) {
    GLuint shaderId;
    shaderId = glCreateShader(type);
    checkGlError("glCreateShader");
    if(shaderId == 0){
        LOGE(TAG_GLUTILS,"create vertex shader error");
        return GL_RESULT_ERROR;
    }
    glShaderSource(shaderId,1,source, nullptr);
    glCompileShader(shaderId);
    GLint compileStatus;
    glGetShaderiv(shaderId,GL_COMPILE_STATUS,&compileStatus);
    if(compileStatus == GL_FALSE){

        GLint infoLen = 0;

        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1) {
            char *infoLog = (char *) malloc(sizeof(char) * infoLen);
            if (infoLog) {
                // 检索信息日志
                glGetShaderInfoLog(shaderId, infoLen, nullptr, infoLog);
                LOGE(TAG_GLUTILS,"GLUtils::loadShader error compiling shader:\n%s\n", infoLog);
                free(infoLog);
            }
            // 删除Shader
            glDeleteShader(shaderId);
            return GL_RESULT_ERROR;
        }
    }
    return shaderId;
}

void GLUtils::checkGlError(const char *pGLOperation) {
    for (GLint error = glGetError(); error; error = glGetError())
    {
        LOGE(TAG_GLUTILS,"CheckGLError after GL Operation %s() glError (0x%x)\n", pGLOperation, error);
    }
}