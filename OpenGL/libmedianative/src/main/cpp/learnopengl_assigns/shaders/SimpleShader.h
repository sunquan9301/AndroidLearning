//
// Created by 孙全 on 2022/5/22.
// article : https://learnopengl-cn.github.io/01%20Getting%20started/05%20Shaders/
// content : vertex transform variable to fragment
// shaders :
//

#ifndef OPENGL_SIMPLESHADER_H
#define OPENGL_SIMPLESHADER_H
#include "learnopengl_assigns/GLAbsRender.h"
static GLuint POS_LOCATION  = 1;
class SimpleShader : public GLAbsRender {
public:
    virtual void onDraw();
    virtual void onSurfaceCreated();
};


#endif //OPENGL_SIMPLESHADER_H
