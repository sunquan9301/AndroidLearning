//
// Created by 孙全 on 2022/5/20.
//
#pragma once
#ifndef OPENGL_RENDERTRIANGLEVBO_H
#define OPENGL_RENDERTRIANGLEVBO_H
#include "learnopengl_assigns/GLAbsRender.h"

class RenderTriangleVBO  : public GLAbsRender{
public:
    RenderTriangleVBO() = default;

    virtual ~RenderTriangleVBO() = default;
    virtual void onDraw();
    virtual void onSurfaceCreated();
    virtual void onDestroy();
};


#endif //OPENGL_RENDERTRIANGLEVBO_H
