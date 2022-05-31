//
// Created by 孙全 on 2022/5/29.
//

#include "StrideShader.h"

static GLfloat vertices[] = {
        0.0f, 0.5f, 0.0f, 1.0f,0.0f,0.0f, // 第一个点（x, y, z）
        -0.5f, -0.5f, 0.0f, 0.0f,1.0f,0.0f,// 第二个点（x, y, z）
        0.5f, -0.5f, 0.0f , 0.0f,0.0f,1.0f// 第三个点（x, y, z）
};

void StrideShader::onDraw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES,0,3);
}

void StrideShader::onSurfaceCreated() {
    glClearColor(0.5f,0.5f,0.5f,1.0f);
    this->m_ProgramObj = GLUtils::createProgram(&this->VERTEX_SHADER,&this->FRAGMENT_SHADER);
    if(this->m_ProgramObj == 0){
        LOGI(TAG_SHADERS_STRIDE_SHADER,"create program error");
        return;
    }
    glUseProgram(this->m_ProgramObj);

    //VBO
//    GLuint VB0;
//    glGenBuffers(1,&VB0);
//    glBindBuffer(GL_ARRAY_BUFFER,VB0);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
//    glVertexAttribPointer(DEFAULT_POS_LOCATION,3,GL_FLOAT,GL_FALSE,6* sizeof(float), nullptr);
//    glEnableVertexAttribArray(DEFAULT_POS_LOCATION);
//    glVertexAttribPointer(DEFAULT_COLOR_LOCATION,3,GL_FLOAT,GL_FALSE,6* sizeof(float),(void*)(3* sizeof(float)));
//    glEnableVertexAttribArray(DEFAULT_COLOR_LOCATION);
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);

//not VBO
    glVertexAttribPointer(DEFAULT_POS_LOCATION,3,GL_FLOAT,GL_FALSE,6* sizeof(float), vertices);
    glEnableVertexAttribArray(DEFAULT_POS_LOCATION);
    glVertexAttribPointer(DEFAULT_COLOR_LOCATION,3,GL_FLOAT,GL_FALSE,6* sizeof(float),(void *)(vertices+3));
    glEnableVertexAttribArray(DEFAULT_COLOR_LOCATION);

}
