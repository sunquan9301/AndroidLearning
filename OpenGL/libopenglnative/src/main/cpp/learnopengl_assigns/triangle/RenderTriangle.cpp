//
// Created by 孙全 on 2022/5/19.
//

#include "RenderTriangle.h"
static GLfloat vertices[] = {
        0.0f, 0.5f, 0.0f, // 第一个点（x, y, z）
        -0.5f, -0.5f, 0.0f, // 第二个点（x, y, z）
        0.5f, -0.5f, 0.0f // 第三个点（x, y, z）
};

void RenderTriangle::onSurfaceCreated() {
    glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
    this->m_ProgramObj = GLUtils::createProgram(&this->VERTEX_SHADER, &this->FRAGMENT_SHADER);
    // 设置清除颜色
    if (!this->m_ProgramObj) {
        LOGD(TAG_RENDER_TRIANGLE,"Could not Create program");
        return;
    }
    glUseProgram(this->m_ProgramObj);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,vertices);
    glEnableVertexAttribArray(0);

}

void RenderTriangle::onDraw() {
    LOGI(TAG_RENDER_TRIANGLE,"onDraw");
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES,0,3);
}