//
// Created by 孙全 on 2022/5/20.
//

#include "RenderRectTwoFragmentShader.h"
float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top
};
float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top
};

void RenderRectTwoFragmentShader::onDraw() {
    LOGI(TAG_RENDER_TWO_FRAGMENT_SHADER,"onDraw");
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(this->m_ProgramObjRED);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES,0,3);

    glUseProgram(this->m_ProgramObjGreen);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES,0,3);
}

void RenderRectTwoFragmentShader::onSurfaceCreated() {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    this->m_ProgramObjRED = GLUtils::createProgram(&this->VERTEX_SHADER, &this->FRAGMENT_SHADER_RED);
    // 设置清除颜色
    if (!this->m_ProgramObjRED) {
        LOGD(TAG_RENDER_TWO_FRAGMENT_SHADER,"Could not Create program red");
        return;
    }
    this->m_ProgramObjGreen = GLUtils::createProgram(&this->VERTEX_SHADER, &this->FRAGMENT_SHADER_GREEN);
    // 设置清除颜色
    if (!this->m_ProgramObjGreen) {
        LOGD(TAG_RENDER_TWO_FRAGMENT_SHADER,"Could not Create program green");
        return;
    }
    glGenVertexArrays(2,VAOs);
    glGenBuffers(2,VBOs);
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[0]);

    glBufferData(GL_ARRAY_BUFFER,sizeof (firstTriangle),firstTriangle,GL_STATIC_DRAW);
    //如果使用了VAO注意最后一个参数要传nullptr
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(0);


    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof (secondTriangle),secondTriangle,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(0);

}

void RenderRectTwoFragmentShader::onInit(JNIEnv *env, jobject asset_manager,
                                         const string &vertexShaderAssetName,
                                         const string &fragmentShaderAssetName) {
    GLUtils::printGLInfo();
    AAssetManager *pManager = AAssetManager_fromJava(env, asset_manager);
    this->VERTEX_SHADER = AssetFun::readAssetFile("hello_triangle_vertex_shader.glsl", pManager);
    this->FRAGMENT_SHADER_RED = AssetFun::readAssetFile("hello_triangle_fragment_shader.glsl", pManager);
    this->FRAGMENT_SHADER_GREEN = AssetFun::readAssetFile("hello_triangle_fragment_shader_green.glsl", pManager);
    LOGI(TAG_RENDER_TWO_FRAGMENT_SHADER,"vertexShaderContent = %s",this->VERTEX_SHADER);
    LOGI(TAG_RENDER_TWO_FRAGMENT_SHADER,"fragmentShaderRed = %s",this->FRAGMENT_SHADER_RED);
    LOGI(TAG_RENDER_TWO_FRAGMENT_SHADER,"fragmentShaderGreen = %s",this->FRAGMENT_SHADER_GREEN);
}
