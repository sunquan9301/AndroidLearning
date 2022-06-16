//
// Created by 孙全 on 2022/6/14.
//

#include "SimpleColorDemo.h"

void SimpleColorDemo::onInit(JNIEnv *env, jobject asset_manager, const string &vertexShaderAssetName,
                        const string &fragmentShaderAssetName) {
    GLUtils::printGLInfo();
    AAssetManager *pManager = AAssetManager_fromJava(env, asset_manager);
    this->VERTEX_SHADER = AssetFun::readAssetFile("lighting_simple_color_vertex_shader.glsl", pManager);
    this->FRAGMENT_SHADER = AssetFun::readAssetFile("lighting_simple_color_object_fragment_shader.glsl", pManager);
    this->FRAGMENT_LIGHT_SHADER = AssetFun::readAssetFile("lighting_simple_color_lightsource_fragment_shader.glsl", pManager);
    LOGI(TAG_LIGHTING_SIMPLE_COLOR,"vertexShaderContent = %s",this->VERTEX_SHADER);
    LOGI(TAG_LIGHTING_SIMPLE_COLOR,"fragmentShaderContent = %s",this->FRAGMENT_SHADER);
    LOGI(TAG_LIGHTING_SIMPLE_COLOR,"fragmentLightSourceShaderContent = %s",this->FRAGMENT_LIGHT_SHADER);
}

void SimpleColorDemo::onDraw() {
//    LOGI(TAG_LIGHTING_SIMPLE_COLOR,"onDraw");
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glUseProgram(m_ProgramObj);
    glBindVertexArray(cubeVAO);
    glm::mat4 value = projection * view * model;
    glUniformMatrix4fv(glGetUniformLocation(m_ProgramObj, "mvp"), 1, GL_FALSE,
                       glm::value_ptr(value));


    glUniform3fv(glGetUniformLocation(m_ProgramObj, "lightColor"), 1,
                       glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
    glUniform3fv(glGetUniformLocation(m_ProgramObj, "objectColor"), 1,
                       glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));
    glDrawArrays(GL_TRIANGLES,0,36);



    glUseProgram(m_ProgramLightObj);
    glBindVertexArray(lightVAO);
    glm::mat4 value1 = projection * view * lightModel;
    glUniformMatrix4fv(glGetUniformLocation(m_ProgramLightObj, "mvp"), 1, GL_FALSE,
                       glm::value_ptr(value1));
    glDrawArrays(GL_TRIANGLES,0,36);
}

void SimpleColorDemo::onSurfaceCreated() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    this->m_ProgramObj = GLUtils::createProgram(&this->VERTEX_SHADER,&this->FRAGMENT_SHADER);
    this->m_ProgramLightObj = GLUtils::createProgram(&this->VERTEX_SHADER,&this->FRAGMENT_LIGHT_SHADER);
    if(m_ProgramObj == 0 || m_ProgramLightObj == 0){
        LOGI(TAG_LIGHTING_SIMPLE_COLOR,"create program error");
        return;
    }

    glGenVertexArrays(1,&cubeVAO);
    glBindVertexArray(cubeVAO);

    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(cubeVertices),cubeVertices,GL_STATIC_DRAW);
    glVertexAttribPointer(DEFAULT_POS_LOCATION,3,GL_FLOAT,GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(DEFAULT_POS_LOCATION);

    glGenVertexArrays(1,&lightVAO);
    glBindVertexArray(lightVAO);
//    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glVertexAttribPointer(DEFAULT_POS_LOCATION,3,GL_FLOAT,GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(DEFAULT_POS_LOCATION);


    projection = glm::perspective(glm::radians(45.0f),3.0f/4.0f,0.1f,100.0f);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    model = glm::rotate(model,glm::radians(-30.0f),glm::vec3(0.0f,1.0f,0.0f));

    lightModel = glm::translate(lightModel,lightPos);
    lightModel = glm::rotate(lightModel,glm::radians(-30.0f),glm::vec3(lightPos.x,1.0f,lightPos.z));
    lightModel = glm::scale(lightModel, glm::vec3(0.2f));
}

void SimpleColorDemo::onOptClick(int optType) {
    if(optType == OPT_RIGHT){
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }else if(optType == OPT_LEFT){
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }else if(optType == OPT_UP){
        cameraPos += cameraSpeed * cameraFront;
    }else if(optType == OPT_DOWN){
        cameraPos -= cameraSpeed * cameraFront;
    }
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

}

void SimpleColorDemo::onDestroy() {
    GLAbsRender::onDestroy();
    LOGI(TAG_LIGHTING_SIMPLE_COLOR,"onDestroy");
    if (m_ProgramLightObj) {
        glDeleteProgram(m_ProgramLightObj);
        m_ProgramLightObj = GL_NONE;
    }
    if(FRAGMENT_LIGHT_SHADER!= nullptr){
        delete[] FRAGMENT_LIGHT_SHADER;
        FRAGMENT_LIGHT_SHADER = nullptr;
    }
}
