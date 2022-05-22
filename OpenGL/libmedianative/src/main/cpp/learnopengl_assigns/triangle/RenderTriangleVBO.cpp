//
// Created by 孙全 on 2022/5/20.
// LearnOpenGL Article: https://learnopengl-cn.github.io/01%20Getting%20started/04%20Hello%20Triangle/
// LearnOpenGL Code: https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.1.hello_triangle/hello_triangle.cpp
//

#include "RenderTriangleVBO.h"
static GLfloat vertices[] = {
        0.0f, 0.8f, 0.0f, // 第一个点（x, y, z）
        -0.8f, -0.8f, 0.0f, // 第二个点（x, y, z）
        0.8f, -0.8f, 0.0f // 第三个点（x, y, z）
};

void RenderTriangleVBO::onDraw() {
    LOGI(TAG_RENDER_TRIANGLE_VBO,"onDraw");
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES,0,3);
}

void RenderTriangleVBO::onSurfaceCreated() {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    this->m_ProgramObj = GLUtils::createProgram(&this->VERTEX_SHADER, &this->FRAGMENT_SHADER);
    // 设置清除颜色
    if (!this->m_ProgramObj) {
        LOGD(TAG_RENDER_TRIANGLE_VBO,"Could not Create program");
        return;
    }
    glUseProgram(this->m_ProgramObj);
    GLuint VB0;
    glGenBuffers(1,&VB0);
    glBindBuffer(GL_ARRAY_BUFFER,VB0);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderTriangleVBO::onDestroy() {
    GLAbsRender::onDestroy();
}
