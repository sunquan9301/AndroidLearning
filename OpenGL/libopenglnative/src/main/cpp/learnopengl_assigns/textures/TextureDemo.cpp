//
// Created by 孙全 on 2022/6/2.
//

#include "TextureDemo.h"
static GLfloat vertics[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
};

static GLfloat vertics1[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.6f, 0.6f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.6f, 0.4f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.4f, 0.4f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.4f, 0.6f  // top left
};

static GLfloat vertics2[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left
};

static GLuint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
};

void TextureDemo::onSurfaceCreated() {
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
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertics2),vertics2,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);


    glVertexAttribPointer(DEFAULT_POS_LOCATION,3,GL_FLOAT,GL_FALSE,8* sizeof(float), nullptr);
    glEnableVertexAttribArray(DEFAULT_POS_LOCATION);

    glVertexAttribPointer(DEFAULT_COLOR_LOCATION,3,GL_FLOAT,GL_FALSE,8* sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(DEFAULT_COLOR_LOCATION);

    glVertexAttribPointer(DEFAULT_TEXTURE_LOCATION,2,GL_FLOAT,GL_FALSE,8* sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(DEFAULT_TEXTURE_LOCATION);

    //GL_ELEMENT_ARRAY_BUFFER不能释放
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    texture = GLUtils::loaderTexture2D(textureMemoryData, textureMemoryDataLen,GL_RGB);
    textureId1 = GLUtils::loaderTexture2D(textureMemoryData1, textureMemoryDataLen1,GL_RGBA);
    if (texture == 0 || textureId1 == 0) {
        LOGE(TAG_TEXTURE_DEMO, "loaderTexture2D error");
    }

    glUniform1i(glGetUniformLocation(m_ProgramObj,"texture"),0);
    glUniform1i(glGetUniformLocation(m_ProgramObj,"texture1"),1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TextureDemo::onDraw() {
    LOGD(TAG_TEXTURE_DEMO,"onDraw start");
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(this->m_ProgramObj);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureId1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void TextureDemo::onInit(JNIEnv *env, jobject asset_manager, const string &vertexShaderAssetName,
                         const string &fragmentShaderAssetName) {
    GLUtils::printGLInfo();
    LOGI(TAG_TEXTURE_DEMO,"vertexShaderAssetName = %s, fragmentShaderAssetName = %s",vertexShaderAssetName.c_str(),fragmentShaderAssetName.c_str());
    AAssetManager *pManager = AAssetManager_fromJava(env, asset_manager);
    this->VERTEX_SHADER = AssetFun::readAssetFile(vertexShaderAssetName.c_str(), pManager);
    this->FRAGMENT_SHADER = AssetFun::readAssetFile(fragmentShaderAssetName.c_str(), pManager);
    this->textureMemoryData = AssetFun::loadImageToMemory("textures/texture_wall.jpg", pManager,
                                                          &textureMemoryDataLen);
    if (textureMemoryData){
        LOGD(TAG_TEXTURE_DEMO,"loadImageToMemory succ len = %d",textureMemoryDataLen);
    }else{
        LOGD(TAG_TEXTURE_DEMO,"loadImageToMemory failure");
    }

    this->textureMemoryData1 = AssetFun::loadImageToMemory("textures/texture_awesomeface.png", pManager,
                                                          &textureMemoryDataLen1);
    if (textureMemoryData1){
        LOGD(TAG_TEXTURE_DEMO,"loadImageToMemory succ len = %d",textureMemoryDataLen1);
    }else{
        LOGD(TAG_TEXTURE_DEMO,"loadImageToMemory failure");
    }
}

void TextureDemo::onDestroy() {
    GLAbsRender::onDestroy();
    if(this->textureMemoryData!= nullptr){
        delete[] textureMemoryData;
        textureMemoryData = nullptr;
    }
    if(this->textureMemoryData1!= nullptr){
        delete[] textureMemoryData1;
        textureMemoryData1 = nullptr;
    }
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture);
    glDeleteTextures(1, &textureId1);
}
