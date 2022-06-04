//
// Created by 孙全 on 2022/6/2.
//

#ifndef OPENGL_TEXTUREDEMO_H
#define OPENGL_TEXTUREDEMO_H
#include "learnopengl_assigns/GLAbsRender.h"

class TextureDemo : public GLAbsRender{
public:
    virtual void onDestroy();
    virtual void onDraw();
    virtual void onSurfaceCreated();
    virtual void onInit(JNIEnv *env,jobject asset_manager,const string &vertexShaderAssetName,const string &fragmentShaderAssetName);
    GLuint VBO,EBO,texture,textureId1;
    int textureMemoryDataLen;
    unsigned char* textureMemoryData;

    int textureMemoryDataLen1;
    unsigned char* textureMemoryData1;
};


#endif //OPENGL_TEXTUREDEMO_H
