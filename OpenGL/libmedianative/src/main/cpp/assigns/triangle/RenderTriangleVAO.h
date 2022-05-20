//
// Created by 孙全 on 2022/5/20.
//
#pragma once
#ifndef OPENGL_RENDERTRIANGLEVAO_H
#define OPENGL_RENDERTRIANGLEVAO_H
#include "assigns/GLAbsRender.h"

class RenderTriangleVAO : public GLAbsRender{
public:
    virtual void onDraw();
    virtual void onSurfaceCreated();
    GLuint VB0,VAO;
};


#endif //OPENGL_RENDERTRIANGLEVAO_H
