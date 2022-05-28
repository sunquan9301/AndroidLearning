//
// Created by 孙全 on 2022/5/22.
//

#include "SimpleShader.h"
static GLfloat vertices[] = {
        0.0f, 0.5f, 0.0f, // 第一个点（x, y, z）
        -0.5f, -0.5f, 0.0f, // 第二个点（x, y, z）
        0.5f, -0.5f, 0.0f // 第三个点（x, y, z）
};
void SimpleShader::onDraw() {
    LOGI(TAG_SHADERS_SIMPLE_SHADER,"onDraw");
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES,0,3);
}

void SimpleShader::onSurfaceCreated() {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    this->m_ProgramObj = GLUtils::createProgram(&this->VERTEX_SHADER, &this->FRAGMENT_SHADER);
    // 设置清除颜色
    if (!this->m_ProgramObj) {
        LOGD(TAG_SHADERS_SIMPLE_SHADER,"Could not Create program");
        return;
    }
    glUseProgram(this->m_ProgramObj);
    glVertexAttribPointer(POS_LOCATION,3,GL_FLOAT,GL_FALSE,0,vertices);
    glEnableVertexAttribArray(POS_LOCATION);
}


