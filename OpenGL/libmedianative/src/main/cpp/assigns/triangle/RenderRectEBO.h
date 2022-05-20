//
// Created by 孙全 on 2022/5/20.
//
#pragma once
#ifndef OPENGL_RENDERRECTEBO_H
#define OPENGL_RENDERRECTEBO_H
#include "assigns/GLAbsRender.h"

class RenderRectEBO : public GLAbsRender{
    virtual void onDraw();
    virtual void onSurfaceCreated();
    GLuint VB0,VEO;
};


#endif //OPENGL_RENDERRECTEBO_H
