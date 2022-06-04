//
// Created by 孙全 on 2022/5/18.
//
#pragma once
#ifndef OPENGL_GLUTILS_H
#define OPENGL_GLUTILS_H

#include "common/LogFun.h"
#include <GLES3/gl32.h>
#include <GLES3/gl3ext.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

class GLUtils {

public:
    /**
     * static  方法
     */

    static void printGLString(const char *name, GLenum s) {
        const char *v = (const char *) glGetString(s);
        LOGI(TAG_GLUTILS,"GL %s = %s \n", name, v);
    }
    // Print some OpenGL info
    static void printGLInfo(){
        printGLString("Version", GL_VERSION);
        printGLString("GLSL Version", GL_SHADING_LANGUAGE_VERSION);
        printGLString("Vendor", GL_VENDOR);
        printGLString("Renderer", GL_RENDERER);
        printGLString("Extensions", GL_EXTENSIONS);
    }

    static GLuint createProgram(const char** vertexSource, const char** fragmentSource);
    static GLuint loaderShader(GLenum type, const char** source);
    static GLuint loaderTexture2D(unsigned char* textureMemData, int textureMemDataLen,GLuint colorFormat);
    static void checkGlError(const char* pGLOperation);
    /**
     * public方法
     */



};


#endif //OPENGL_GLUTILS_H
