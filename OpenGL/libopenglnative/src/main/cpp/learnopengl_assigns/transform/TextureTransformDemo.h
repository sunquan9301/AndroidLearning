//
// Created by 孙全 on 2022/6/13.
//

#ifndef OPENGL_TEXTURETRANSFORMDEMO_H
#define OPENGL_TEXTURETRANSFORMDEMO_H
#include "learnopengl_assigns/GLAbsRender.h"

class TextureTransformDemo : public GLAbsRender{
public:
    virtual void onDraw();
    virtual void onDestroy();
    virtual void onSurfaceCreated();
    virtual void onInit(JNIEnv *env,jobject asset_manager,const string &vertexShaderAssetName,const string &fragmentShaderAssetName);
    virtual void onOptClick(int optType);

    GLuint VBO,EBO,textureId,textureId1;
    unsigned char* textureMemData;
    int textureMemoryDataLen;

    unsigned char* textureMemData1;
    int textureMemoryDataLen1;
    glm::mat4 model,view,projection;

    TextureTransformDemo(){
        model = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);
    }
};


#endif //OPENGL_TEXTURETRANSFORMDEMO_H
