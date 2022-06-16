//
// Created by 孙全 on 2022/6/14.
//

#ifndef OPENGL_SIMPLECOLORDEMO_H
#define OPENGL_SIMPLECOLORDEMO_H
#include "learnopengl_assigns/GLAbsRender.h"
#include "objects/CubeVertices.h"
class SimpleColorDemo: public GLAbsRender{
public:
    virtual void onInit(JNIEnv *env,jobject asset_manager,const string &vertexShaderAssetName,const string &fragmentShaderAssetName);
    virtual void onDraw();
    virtual void onSurfaceCreated();
    virtual void onOptClick(int optType);
    virtual void onDestroy();

    GLuint cubeVAO,VBO,lightVAO;

    const char *FRAGMENT_LIGHT_SHADER;

    GLuint m_ProgramLightObj;

    glm::mat4 model,view,projection,lightModel;

    glm::vec3 cameraPos,cameraFront,cameraUp,lightPos;
    float cameraSpeed = 1.0f;

    SimpleColorDemo(){
        model = glm::mat4(1.0f);
        lightModel = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);


        cameraPos   = glm::vec3(0.0f, 0.0f,  10.0f);
        cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
        lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
        cameraSpeed = 1.0f;
    }
};


#endif //OPENGL_SIMPLECOLORDEMO_H
