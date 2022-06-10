//
// Created by 孙全 on 2022/6/4.
//

#ifndef OPENGL_TRANSFORMDEMO_H
#define OPENGL_TRANSFORMDEMO_H
#include "learnopengl_assigns/GLAbsRender.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TransformDemo : public GLAbsRender {
public:
    virtual void onDraw();
    virtual void onDestroy();
    virtual void onSurfaceCreated();
    virtual void onInit(JNIEnv *env,jobject asset_manager,const string &vertexShaderAssetName,const string &fragmentShaderAssetName);
    virtual void onOptClick(int optType);
    GLuint EBO,VBO,textureId;
    unsigned char* textureMemData;
    int textureMemoryDataLen;
    glm::mat4 model,view,projection;

    TransformDemo(){
        model = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);
    }
};


#endif //OPENGL_TRANSFORMDEMO_H
