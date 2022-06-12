//
// Created by 孙全 on 2022/6/4.
//

#include "TransformDemo.h"

static GLfloat vertics[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
};


static GLuint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
};

void TransformDemo::onDraw() {
    LOGD(TAG_TEXTURE_DEMO, "onDraw start");
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(m_ProgramObj);
    glm::mat4 value = projection * view * model;
    glUniformMatrix4fv(glGetUniformLocation(m_ProgramObj, "transform"), 1, GL_FALSE,
                       glm::value_ptr(value));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void TransformDemo::onSurfaceCreated() {
    glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
    this->m_ProgramObj = GLUtils::createProgram(&this->VERTEX_SHADER,&this->FRAGMENT_SHADER);
    if(!this->m_ProgramObj){
        LOGD(TAG_TEXTURE_DEMO,"Could not Create program");
        return;
    }
    glUseProgram(this->m_ProgramObj);

    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertics),vertics,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);


    glVertexAttribPointer(DEFAULT_POS_LOCATION,3,GL_FLOAT,GL_FALSE,8* sizeof(float), nullptr);
    glEnableVertexAttribArray(DEFAULT_POS_LOCATION);

    glVertexAttribPointer(DEFAULT_COLOR_LOCATION,3,GL_FLOAT,GL_FALSE,8* sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(DEFAULT_COLOR_LOCATION);

    glVertexAttribPointer(DEFAULT_TEXTURE_LOCATION,2,GL_FLOAT,GL_FALSE,8* sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(DEFAULT_TEXTURE_LOCATION);

    //GL_ELEMENT_ARRAY_BUFFER不能释放
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    textureId = GLUtils::loaderTexture2D(textureMemData, textureMemoryDataLen,GL_RGBA);
//    textureId1 = GLUtils::loaderTexture2D(textureMemoryData1, textureMemoryDataLen1,GL_RGBA);
    if (textureId == 0 ) {
        LOGE(TAG_TEXTURE_DEMO, "loaderTexture2D error");
    }

//    glm::mat4 rotate = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f,0.0f,1.0f));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void TransformDemo::onDestroy() {
    GLAbsRender::onDestroy();
    if(this->textureMemData!= nullptr){
        delete[] textureMemData;
        textureMemData = nullptr;
    }

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &textureId);
}

void TransformDemo::onInit(JNIEnv *env, jobject asset_manager, const string &vertexShaderAssetName,
                           const string &fragmentShaderAssetName) {
    GLUtils::printGLInfo();
    LOGI(TAG_TEXTURE_DEMO,"vertexShaderAssetName = %s, fragmentShaderAssetName = %s",vertexShaderAssetName.c_str(),fragmentShaderAssetName.c_str());
    AAssetManager *pManager = AAssetManager_fromJava(env, asset_manager);
    this->VERTEX_SHADER = AssetFun::readAssetFile(vertexShaderAssetName.c_str(), pManager);
    this->FRAGMENT_SHADER = AssetFun::readAssetFile(fragmentShaderAssetName.c_str(), pManager);
    this->textureMemData = AssetFun::loadImageToMemory("textures/texture_awesomeface.png", pManager,
                                                          &textureMemoryDataLen);
    if (textureMemData){
        LOGD(TAG_TEXTURE_DEMO,"loadImageToMemory succ len = %d",textureMemoryDataLen);
    }else{
        LOGD(TAG_TEXTURE_DEMO,"loadImageToMemory failure");
    }

//    this->textureMemoryData1 = AssetFun::loadImageToMemory("textures/texture_awesomeface.png", pManager,
//                                                           &textureMemoryDataLen1);
//    if (textureMemoryData1){
//        LOGD(TAG_TEXTURE_DEMO,"loadImageToMemory succ len = %d",textureMemoryDataLen1);
//    }else{
//        LOGD(TAG_TEXTURE_DEMO,"loadImageToMemory failure");
//    }
}

void TransformDemo::onOptClick(int optType) {
    // model矩阵，是指把模型摆在什么地方，因此你会看到随着案件，箱子会上下左右移动，并沿着z轴方向旋转。
    if(optType == OPT_RIGHT){
        model = glm::translate(model,glm::vec3(0.1f,0.0f,0.0f));
    }else if(optType == OPT_LEFT){
        model = glm::translate(model,glm::vec3(-0.1f,0.0f,0.0f));
    }else if(optType == OPT_UP){
        model = glm::translate(model,glm::vec3(0.0f,0.1f,0.0f));
    }else if(optType == OPT_DOWN){
        model = glm::translate(model,glm::vec3(0.0f,-0.1f,0.0f));
    }else if(optType == OPT_ROTATE_RIGHT){
//        model = glm::rotate(model,glm::radians(-5.0f), glm::vec3(0.0f,0.0f,1.0f));
        model = glm::rotate(model,glm::radians(-5.0f), glm::vec3(1.0f,0.0f,0.0f));
    }else if(optType == OPT_ROTATE_LEFT){
        model = glm::rotate(model,glm::radians(5.0f), glm::vec3(0.0f,0.0f,1.0f));
    }
}
