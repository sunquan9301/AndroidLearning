//
// Created by 孙全 on 2022/5/18.
//
#include <cstdlib>
#include "GLUtils.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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

GLuint GLUtils::loaderTexture2D(unsigned char *textureMemData, int textureMemDataLen,GLuint colorFormat) {
    GLuint textureId;
    glGenTextures(1,&textureId);
    if(textureId == 0){
        LOGE(TAG_GLUTILS,"create texture error");
        return GL_RESULT_ERROR;
    }
    glBindTexture(GL_TEXTURE_2D,textureId);
    // set the texture wrapping parameters
    //GL_CLAMP_TO_BORDER在gl32.h头文件里才包含

    //纹理坐标的范围通常是从(0, 0)到(1, 1)，那如果我们把纹理坐标设置在范围之外会发生什么？OpenGL默认的行为是重复这个纹理图像（我们基本上忽略浮点纹理坐标的整数部分）
    //坐标设置在纹理之外才会生效
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width,height,channel;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load_from_memory(textureMemData,
                                                textureMemDataLen, &width, &height,
                                                &channel, 0);
    if(data){
        LOGE(TAG_GLUTILS,"load texture image succ w = %d,h = %d,channel=%d",width,height,channel);
        glTexImage2D(GL_TEXTURE_2D,0,colorFormat,width,height,0,colorFormat,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        LOGE(TAG_GLUTILS,"could not load texture image");
    }
    stbi_image_free(data);
    return textureId;
}
