//
// Created by 孙全 on 2022/5/20.
// Learn OpenGL exercise1:https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.3.hello_triangle_exercise1/hello_triangle_exercise1.cpp
//

#include "RenderRect.h"
static float vertices[] = {
        // 第一个三角形
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, 0.5f, 0.0f,  // 左上角
        // 第二个三角形
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
};

void RenderRect::onDraw() {
    LOGI(TAG_RENDER_RECT,"onDraw");
    glClear(GL_COLOR_BUFFER_BIT);
    // glDrawArrays函数第一个参数是我们打算绘制的OpenGL图元的类型。我们希望绘制的是一个三角形，这里传递GL_TRIANGLES给它。
    // 第二个参数指定了顶点数组的起始索引，我们这里填0。
    // 最后一个参数指定我们打算绘制多少个顶点，这里是3（我们只从我们的数据中渲染一个三角形，它只有3个顶点长）。
    // 主意这里count 是绘制定点个个数，不是三角形的个数， 6个定点+ 三角形类型 => 2个三角形
    glDrawArrays(GL_TRIANGLES,0,6);

    //Other Correct Demo:
    //这里先绘制3个顶点，一个三角形 index ： 0，1，2；然后绘制另外3个顶点index：3，4，5
    //glDrawArrays(GL_TRIANGLES,0,3);
    //glDrawArrays(GL_TRIANGLES,3,3);

    //Error Demo1:
    //这里只能绘制三个顶点，绘制不出来rect
    //glDrawArrays(GL_TRIANGLES,0,3);
    //这里类似从index：3 开始绘制6个定点，超出限制
    //glDrawArrays(GL_TRIANGLES,3,6);



}
void RenderRect::onSurfaceCreated() {
    this->m_ProgramObj = GLUtils::createProgram(&this->VERTEX_SHADER, &this->FRAGMENT_SHADER);
    // 设置清除颜色
    if (!this->m_ProgramObj) {
        LOGD(TAG_RENDER_RECT,"Could not Create program");
        return;
    }
    glUseProgram(this->m_ProgramObj);
    // 第一个参数顶点属性。=> vertex shader location =>  layout(location = 0) in vec4 vPosition;
    // 第二个顶点属性的大小。顶点属性是一个vec3，所以是3
    // 第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec*都是由浮点数值组成的)。
    // 第四个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。我们把它设置为GL_FALSE。
    // 第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。我们设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。
    //      一旦我们有更多的顶点属性，我们就必须更小心地定义每个顶点属性之间的间隔，
    //      （译注: 这个参数的意思简单说就是从这个属性第二次出现的地方到整个数组0位置之间有多少字节）。
    // 最后一个参数的类型是void*，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。


    // rect里
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,vertices);

    //Error Demo1：下是错误的，第二个size是顶点属性的大小，不是顶点的个数
    //glVertexAttribPointer(0,6,GL_FLOAT,GL_FALSE,0,vertices);

    glEnableVertexAttribArray(0);
}
