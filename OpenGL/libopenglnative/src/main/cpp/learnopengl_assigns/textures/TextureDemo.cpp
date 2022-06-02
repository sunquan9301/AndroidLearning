//
// Created by 孙全 on 2022/6/2.
//

#include "TextureDemo.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
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

void TextureDemo::onSurfaceCreated() {
    glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
    this->m_ProgramObj = GLUtils::createProgram(&this->VERTEX_SHADER,&this->FRAGMENT_SHADER);
    if(!this->m_ProgramObj){
        LOGD(TAG_TEXTURE_DEMO,"Could not Create program");
        return;
    }
    glUseProgram(this->m_ProgramObj);

    glGenBuffers(1,&VB0);
    glGenBuffers(1,&VEO);
    glBindBuffer(GL_ARRAY_BUFFER,VB0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,VEO);
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


//bind texture
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width,height,channel;
    unsigned char *data = stbi_load_from_memory(this->textureMemoryData,
                                                        textureMemoryDataLen, &width, &height,
                                                        &channel, 0);
    if(data){
        LOGE(TAG_TEXTURE_DEMO,"load texture image succ w = %d,h = %d,channel=%d",width,height,channel);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        LOGE(TAG_TEXTURE_DEMO,"could not load texture image");
    }
    stbi_image_free(data);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TextureDemo::onDraw() {
    LOGD(TAG_TEXTURE_DEMO,"onDraw start");
    glClear(GL_COLOR_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, texture);
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
}

void TextureDemo::onDestroy() {
    GLAbsRender::onDestroy();
    if(this->textureMemoryData!= nullptr){
        delete[] textureMemoryData;
        textureMemoryData = nullptr;
    }
}
