//
// Created by 孙全 on 2022/6/13.
//

#include "TextureTransformDemo.h"
static GLfloat vertics[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

static glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};

static glm::vec3 viewEye = glm::vec3( 0.0f,  0.0f,  10.0f);
static float rotateEye = 0.0f;

static float cameraSpeed = 1.0f;
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  10.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
int deltaTime = 0; // 当前帧与上一帧的时间差
long lastFrame = 0; // 上一帧的时间

void TextureTransformDemo::onDraw() {
    long currentFrame = clock();
//    deltaTime = currentFrame - lastFrame;
//    lastFrame = currentFrame;
    LOGI(TAG_TEXTURE_TRANSFORM_DEMO,"currentFrame = %ld",currentFrame);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glUseProgram(m_ProgramObj);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureId1);
    for(int i=0;i<10;i++){
        glm::mat4 modelTemp(1.0f);
        modelTemp = glm::translate(modelTemp, cubePositions[i]);
        float angle = 20.0f * i;
        modelTemp = glm::rotate(modelTemp, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        glm::mat4 value = projection * view * modelTemp;
        glUniformMatrix4fv(glGetUniformLocation(m_ProgramObj, "transform"), 1, GL_FALSE,
                           glm::value_ptr(value));
        glDrawArrays(GL_TRIANGLES,0,36);
    }
}

void TextureTransformDemo::onSurfaceCreated() {
    glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    this->m_ProgramObj = GLUtils::createProgram(&this->VERTEX_SHADER, &this->FRAGMENT_SHADER);
    if (m_ProgramObj == 0) {
        LOGI(TAG_TEXTURE_TRANSFORM_DEMO, "create program error");
        return;
    }

    glUseProgram(this->m_ProgramObj);
    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertics), vertics, GL_STATIC_DRAW);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(DEFAULT_POS_LOCATION, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(DEFAULT_POS_LOCATION);
//    glVertexAttribPointer(DEFAULT_COLOR_LOCATION, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
//                          (void *) (3 * sizeof(float)));
//    glEnableVertexAttribArray(DEFAULT_COLOR_LOCATION);

    glVertexAttribPointer(DEFAULT_TEXTURE_LOCATION, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(DEFAULT_TEXTURE_LOCATION);

    textureId = GLUtils::loaderTexture2D(textureMemData,textureMemoryDataLen,GL_RGBA);
    textureId1 = GLUtils::loaderTexture2D(textureMemData1,textureMemoryDataLen1,GL_RGB);
    glUniform1i(glGetUniformLocation(m_ProgramObj,"texture"),0);
    glUniform1i(glGetUniformLocation(m_ProgramObj,"texture1"),1);


    if (textureId == 0 ) {
        LOGE(TAG_TEXTURE_TRANSFORM_DEMO, "loaderTexture2D error");
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    projection = glm::perspective(glm::radians(45.0f),0.75f,0.1f,100.0f);
    view = glm::translate(view,-1.0f*viewEye);
//    model = glm::rotate(model,glm::radians(-45.0f),glm::vec3(1.0f,1.0f,0.0f));
//    view = glm::translate(view,glm::vec3(0.0f,0.0f,-10.0f));
}

void TextureTransformDemo::onOptClick(int optType) {
    // model矩阵，是指把模型摆在什么地方，因此你会看到随着案件，箱子会上下左右移动，并沿着z轴方向旋转。
    //应该用一个变量记住值来算view的坐标点。
    float cameraSpeed = 20.0f * deltaTime/1000.0f;
    LOGI(TAG_TEXTURE_TRANSFORM_DEMO,"deltaTime = %d, cameraSpeed = %f",deltaTime,cameraSpeed);
    if(optType == OPT_RIGHT){
//        viewEye = viewEye + glm::vec3 (0.1f,0.0f,0.0f);
//        view = glm::translate(view,glm::vec3(-0.1f,0.0f,0.0f));
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    }else if(optType == OPT_LEFT){
//        viewEye = viewEye + glm::vec3 (-0.1f,0.0f,0.0f);
//        view = glm::translate(view,glm::vec3(0.1f,0.0f,0.0f));
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }else if(optType == OPT_UP){
//        viewEye = viewEye + glm::vec3 (0.0f,0.0f,-0.1f);

//        view = glm::translate(view,glm::vec3(0.0f,0.0f,0.1f));
        cameraPos += cameraSpeed * cameraFront;
    }else if(optType == OPT_DOWN){
//        viewEye = viewEye + glm::vec3 (0.0f,0.0f,0.1f);
//        view = glm::translate(view,glm::vec3(0.0f,0.0f,-0.1f));
        cameraPos -= cameraSpeed * cameraFront;
    }else if(optType == OPT_ROTATE_RIGHT){
        rotateEye = rotateEye+5.0f;
//        view = glm::rotate(view,glm::radians(-5.0f), glm::vec3(0.0f,1.0f,0.0f));
    }else if(optType == OPT_ROTATE_LEFT){
        rotateEye = rotateEye-5.0f;
//        view = glm::rotate(view,glm::radians(5.0f), glm::vec3(0.0f,1.0f,0.0f));
    }
//    glm::mat4 viewInit(1.0f);
//    view = glm::translate(viewInit,-1.0f*viewEye);
//    view = glm::rotate(view,glm::radians(-rotateEye),glm::vec3(viewEye.x,1.0f,0.0f));

    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

}

void TextureTransformDemo::onInit(JNIEnv *env, jobject asset_manager,
                                  const string &vertexShaderAssetName,
                                  const string &fragmentShaderAssetName) {
    GLUtils::printGLInfo();
    LOGI(TAG_TEXTURE_TRANSFORM_DEMO, "vertexShaderAssetName = %s, fragmentShaderAssetName = %s",
         vertexShaderAssetName.c_str(), fragmentShaderAssetName.c_str());
    AAssetManager *pManager = AAssetManager_fromJava(env, asset_manager);
    this->VERTEX_SHADER = AssetFun::readAssetFile(vertexShaderAssetName.c_str(), pManager);
    this->FRAGMENT_SHADER = AssetFun::readAssetFile(fragmentShaderAssetName.c_str(), pManager);
    this->textureMemData = AssetFun::loadImageToMemory("textures/texture_awesomeface.png",
                                                       pManager,
                                                       &textureMemoryDataLen);
    this->textureMemData1 = AssetFun::loadImageToMemory("textures/texture_wall.jpg",
                                                       pManager,
                                                       &textureMemoryDataLen1);

    if (textureMemData) {
        LOGD(TAG_TEXTURE_DEMO, "loadImageToMemory succ len = %d", textureMemoryDataLen);
    } else {
        LOGD(TAG_TEXTURE_DEMO, "loadImageToMemory failure");
    }
}

void TextureTransformDemo::onDestroy() {
    GLAbsRender::onDestroy();
    if(this->textureMemData!= nullptr){
        delete[] textureMemData;
        textureMemData = nullptr;
    }
    if(this->textureMemData1!= nullptr){
        delete[] textureMemData1;
        textureMemData1 = nullptr;
    }

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &textureId);
    glDeleteTextures(1, &textureId1);
}

