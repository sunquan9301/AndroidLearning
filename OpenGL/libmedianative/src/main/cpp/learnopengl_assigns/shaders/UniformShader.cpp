//
// Created by 孙全 on 2022/5/28.
//

#include "UniformShader.h"
static GLfloat vertices[] = {
        0.0f, 0.5f, 0.0f, // 第一个点（x, y, z）
        -0.5f, -0.5f, 0.0f, // 第二个点（x, y, z）
        0.5f, -0.5f, 0.0f // 第三个点（x, y, z）
};
static GLfloat greenColor = 1;
void UniformShader::onDraw() {
    LOGI(TAG_SHADERS_SIMPLE_SHADER,"onDraw");
    glUseProgram(this->m_ProgramObj);

    //assign1 :  change color
//    greenColor+=1;
//    float d = (sin(greenColor/10.0f) / 2.0f) + 0.5f;
//    LOGI(TAG_SHADERS_SIMPLE_SHADER,"greenColor = %f, value = %f",greenColor,d);
//    glUniform4f(this->uniformLoc,1.0f,d,0.0f,0.0f);

    //assign2:
    //transform triangle
//    float d1 = (sin(greenColor/10.0f) / 2.0f);
//    glUniform1f(this->uniformXTransOffsetLoc,d1);
////    glUniform1f(this->uniformXTransOffsetLoc,0.0f);



    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES,0,3);
}

void UniformShader::onSurfaceCreated() {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    this->m_ProgramObj = GLUtils::createProgram(&this->VERTEX_SHADER, &this->FRAGMENT_SHADER);
    // 设置清除颜色
    if (!this->m_ProgramObj) {
        LOGD(TAG_SHADERS_SIMPLE_SHADER,"Could not Create program");
        return;
    }

    glVertexAttribPointer(DEFAULT_POS_LOCATION,3,GL_FLOAT,GL_FALSE,0,vertices);
    glEnableVertexAttribArray(DEFAULT_POS_LOCATION);
}
