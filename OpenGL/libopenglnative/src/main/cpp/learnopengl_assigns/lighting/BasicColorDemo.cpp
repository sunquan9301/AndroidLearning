//
// Created by 孙全 on 2022/6/14.
//

#include "BasicColorDemo.h"

void BasicColorDemo::onInit(JNIEnv *env, jobject asset_manager, const string &vertexShaderAssetName,
                             const string &fragmentShaderAssetName) {
    GLUtils::printGLInfo();
    AAssetManager *pManager = AAssetManager_fromJava(env, asset_manager);
    this->VERTEX_SHADER = AssetFun::readAssetFile("lighting_basic_color_object_vertex_shader.glsl", pManager);
    this->FRAGMENT_SHADER = AssetFun::readAssetFile("lighting_basic_color_object_fragment_shader.glsl", pManager);
    this->VERTICS_LIGHT_SHADER = AssetFun::readAssetFile("lighting_basic_color_lightsource_vertex_shader.glsl", pManager);
    this->FRAGMENT_LIGHT_SHADER = AssetFun::readAssetFile("lighting_basic_color_lightsource_fragment_shader.glsl", pManager);
    LOGI(TAG_LIGHTING_SIMPLE_COLOR,"vertexShaderContent = %s",this->VERTEX_SHADER);
    LOGI(TAG_LIGHTING_SIMPLE_COLOR,"fragmentShaderContent = %s",this->FRAGMENT_SHADER);
    LOGI(TAG_LIGHTING_SIMPLE_COLOR,"fragmentLightSourceShaderContent = %s",this->FRAGMENT_LIGHT_SHADER);
    LOGI(TAG_LIGHTING_SIMPLE_COLOR,"verticesLightSourceShaderContent = %s",this->VERTICS_LIGHT_SHADER);
}

void BasicColorDemo::onDraw() {
    LOGI(TAG_LIGHTING_SIMPLE_COLOR,"onDraw");
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glUseProgram(m_ProgramObj);

    glUniform3fv(glGetUniformLocation(m_ProgramObj, "lightColor"), 1,
                 glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
    glUniform3fv(glGetUniformLocation(m_ProgramObj, "objectColor"), 1,
                 glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));
    glUniform3fv(glGetUniformLocation(m_ProgramObj, "lightPos"), 1,
                 glm::value_ptr(lightPos));

    glUniformMatrix4fv(glGetUniformLocation(m_ProgramObj, "view"), 1, GL_FALSE,
                       glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(m_ProgramObj, "model"), 1, GL_FALSE,
                       glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(m_ProgramObj, "projection"), 1, GL_FALSE,
                       glm::value_ptr(projection));
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES,0,36);



    glUseProgram(m_ProgramLightObj);

    lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);
    lightModel = glm::scale(lightModel, glm::vec3(0.2f));
    glUniformMatrix4fv(glGetUniformLocation(m_ProgramLightObj, "view"), 1, GL_FALSE,
                       glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(m_ProgramLightObj, "model"), 1, GL_FALSE,
                       glm::value_ptr(lightModel));
    glUniformMatrix4fv(glGetUniformLocation(m_ProgramLightObj, "projection"), 1, GL_FALSE,
                       glm::value_ptr(projection));
    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES,0,36);
}

void BasicColorDemo::onSurfaceCreated() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    this->m_ProgramObj = GLUtils::createProgram(&this->VERTEX_SHADER,&this->FRAGMENT_SHADER);
    this->m_ProgramLightObj = GLUtils::createProgram(&this->VERTICS_LIGHT_SHADER,&this->FRAGMENT_LIGHT_SHADER);
    if(m_ProgramObj == 0 || m_ProgramLightObj == 0){
        LOGI(TAG_LIGHTING_SIMPLE_COLOR,"create program error");
        return;
    }

    glGenVertexArrays(1,&cubeVAO);
    glGenBuffers(1,&VBO);


    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(cubeVertices),cubeVertices,GL_STATIC_DRAW);
    glBindVertexArray(cubeVAO);

    glVertexAttribPointer(DEFAULT_POS_LOCATION,3,GL_FLOAT,GL_FALSE,6*sizeof(float ), nullptr);
    glEnableVertexAttribArray(DEFAULT_POS_LOCATION);
    glVertexAttribPointer(DEFAULT_NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),(void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(DEFAULT_NORMAL_LOCATION);


    glGenVertexArrays(1,&lightVAO);
    glBindVertexArray(lightVAO);
//    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glVertexAttribPointer(DEFAULT_POS_LOCATION,3,GL_FLOAT,GL_FALSE,6*sizeof(float ), nullptr);
    glEnableVertexAttribArray(DEFAULT_POS_LOCATION);


    projection = glm::perspective(glm::radians(45.0f),3.0f/4.0f,0.1f,100.0f);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    model = glm::rotate(model,glm::radians(-60.0f),glm::vec3(0.0f,1.0f,0.0f));
    lightModel = glm::rotate(model,glm::radians(-60.0f),glm::vec3(0.0f,1.0f,0.0f));

}

void BasicColorDemo::onOptClick(int optType) {
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

void BasicColorDemo::onDestroy() {
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
    if(VERTICS_LIGHT_SHADER!= nullptr){
        delete[] VERTICS_LIGHT_SHADER;
        VERTICS_LIGHT_SHADER = nullptr;
    }
}
