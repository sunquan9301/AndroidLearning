//
// Created by 孙全 on 2022/5/22.
//

#ifndef OPENGL_SIMPLESHADERV2_H
#define OPENGL_SIMPLESHADERV2_H
#include "learnopengl_assigns/GLAbsRenderV2.h"

class SimpleShaderV2 : public GLAbsRenderV2{
    virtual void onDraw();
    virtual void onSurfaceCreated();
    virtual void onInit(JNIEnv *env,jobject asset_manager);
};


#endif //OPENGL_SIMPLESHADERV2_H
