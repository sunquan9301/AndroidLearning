//
// Created by 孙全 on 2022/5/15.
//

#include "EGLRender.h"

static GLfloat vertices[] = {
        0.0f, 0.5f, 0.0f, // 第一个点（x, y, z）
        -0.5f, -0.5f, 0.0f, // 第二个点（x, y, z）
        0.5f, -0.5f, 0.0f // 第三个点（x, y, z）
};

EGLRender *EGLRender::m_Instance = new EGLRender();


EGLRender *EGLRender::getInstance() {
    return m_Instance;
}

EGLRender::EGLRender() {
    VERTEX_SHADER = GL_NONE;
    FRAGMENT_SHADER = GL_NONE;
    m_ProgramObj = 0;
    m_Width = 0;
    m_Height = 0;
}

EGLRender::~EGLRender() = default;


void EGLRender::onDraw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES,0,3);
}

void EGLRender::onSurfaceChange(int width, int height) {
    LOGI(TAG_EGL_RENDER,"onSurfaceChange, width = %d, height = %d",width,height);
    this->m_Width = width;
    this->m_Height = height;
    glViewport(0,0,width,height);
}

void EGLRender::onDestroy() {
    if (this->m_ProgramObj) {
        glDeleteProgram(this->m_ProgramObj);
        m_ProgramObj = GL_NONE;
    }
    if(this->VERTEX_SHADER != nullptr){
        delete[] this->VERTEX_SHADER;
        this->VERTEX_SHADER = nullptr;
    }
    if(this->FRAGMENT_SHADER!= nullptr){
        delete[] this->FRAGMENT_SHADER;
        this->FRAGMENT_SHADER = nullptr;
    }
}

void EGLRender::onInit(JNIEnv *env, jobject asset_manager, const string &vertexShaderAssetName,
                       const string &fragmentShaderAssetName) {
    GLUtils::printGLInfo();
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    LOGI(TAG_EGL_RENDER,"vertexShaderAssetName = %s, fragmentShaderAssetName = %s",vertexShaderAssetName.c_str(),fragmentShaderAssetName.c_str());
    AAssetManager *pManager = AAssetManager_fromJava(env, asset_manager);
    this->VERTEX_SHADER = AssetFun::readAssetFile(vertexShaderAssetName.c_str(), pManager);
    this->FRAGMENT_SHADER = AssetFun::readAssetFile(fragmentShaderAssetName.c_str(), pManager);
    LOGI(TAG_EGL_RENDER,"vertexShaderContent = %s",this->VERTEX_SHADER);
    LOGI(TAG_EGL_RENDER,"fragmentShaderContent = %s",this->FRAGMENT_SHADER);
}

void EGLRender::onSurfaceCreated() {
    this->m_ProgramObj = GLUtils::createProgram(&this->VERTEX_SHADER, &this->FRAGMENT_SHADER);
    // 设置清除颜色
    if (!this->m_ProgramObj) {
        LOGD(TAG_EGL_RENDER,"Could not Create program");
        return;
    }
    glUseProgram(this->m_ProgramObj);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,vertices);
    glEnableVertexAttribArray(0);
}


