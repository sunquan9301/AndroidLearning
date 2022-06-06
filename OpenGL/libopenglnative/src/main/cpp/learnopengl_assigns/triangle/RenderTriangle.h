//
// Created by 孙全 on 2022/5/19.
//
#pragma once
#ifndef OPENGL_RENDERTRIANGLE_H
#define OPENGL_RENDERTRIANGLE_H
#include "learnopengl_assigns/GLAbsRender.h"


class RenderTriangle : public GLAbsRender{
public:
    virtual void onDraw();
    virtual void onSurfaceCreated();
};


#endif //OPENGL_RENDERTRIANGLE_H
