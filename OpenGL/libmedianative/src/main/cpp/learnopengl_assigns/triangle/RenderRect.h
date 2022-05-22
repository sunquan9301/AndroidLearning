//
// Created by 孙全 on 2022/5/20.
//
#pragma once
#ifndef OPENGL_RENDERRECT_H
#define OPENGL_RENDERRECT_H
#include "learnopengl_assigns/GLAbsRender.h"

class RenderRect : public GLAbsRender{
public:
    virtual void onDraw();
    virtual void onSurfaceCreated();
    GLuint VB0,VAO;
};


#endif //OPENGL_RENDERRECT_H
