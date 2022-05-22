//
// Created by 孙全 on 2022/5/20.
//

#include "RenderRectEBO.h"
float vertices[] = {
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
};

unsigned int indices[] = { // 注意索引从0开始!
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
};

void RenderRectEBO::onDraw() {
    LOGI(TAG_RENDER_RECT_EBO,"onDraw");
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void RenderRectEBO::onSurfaceCreated() {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    this->m_ProgramObj = GLUtils::createProgram(&this->VERTEX_SHADER, &this->FRAGMENT_SHADER);
    // 设置清除颜色
    if (!this->m_ProgramObj) {
        LOGD(TAG_RENDER_RECT_EBO,"Could not Create program");
        return;
    }
    glUseProgram(this->m_ProgramObj);
    glGenBuffers(1,&VB0);
    glGenBuffers(1,&VEO);
    glBindBuffer(GL_ARRAY_BUFFER,VB0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,VEO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);


    glVertexAttribPointer(DEFAULT_POS_LOCATION,3,GL_FLOAT,GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(DEFAULT_POS_LOCATION);


}
