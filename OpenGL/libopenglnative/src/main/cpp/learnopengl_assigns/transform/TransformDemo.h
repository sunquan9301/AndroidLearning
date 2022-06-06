//
// Created by 孙全 on 2022/6/4.
//

#ifndef OPENGL_TRANSFORMDEMO_H
#define OPENGL_TRANSFORMDEMO_H
#include "learnopengl_assigns/GLAbsRender.h"

class TransformDemo : public GLAbsRender {
public:
    virtual void onDraw();
    virtual void onDestroy();
    virtual void onSurfaceCreated();
    virtual void onInit(JNIEnv *env,jobject asset_manager,const string &vertexShaderAssetName,const string &fragmentShaderAssetName);

    GLuint EBO,VBO,textureId;
    unsigned char* textureMemData;
    int textureMemoryDataLen;
};


#endif //OPENGL_TRANSFORMDEMO_H
