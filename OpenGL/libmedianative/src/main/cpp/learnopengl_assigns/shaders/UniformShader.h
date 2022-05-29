//
// Created by 孙全 on 2022/5/28.
//

#ifndef OPENGL_UNIFORMSHADER_H
#define OPENGL_UNIFORMSHADER_H
#include "learnopengl_assigns/GLAbsRender.h"
class UniformShader: public GLAbsRender {
public:
    virtual void onDraw();
    virtual void onSurfaceCreated();
    GLint uniformLoc = 1;
    GLint uniformXTransOffsetLoc = 2;
};


#endif //OPENGL_UNIFORMSHADER_H
