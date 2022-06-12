//
// Created by 孙全 on 2022/6/12.
//

#include "PerspactiveTransformDemo.h"
static GLfloat vertexs[] = {
        2.0, 0.0, -2.0, 0.0f, 1.0f, 0.0f,//左
        0.0, 2.0, -2.0, 0.0f, 1.0f, 0.0f, //上
        -2.0, 0.0, -2.0, 0.0f, 1.0f, 0.0f,//右
        3.5, -1.0, -5.0, 0.0f, 0.0f, 1.0f,
        2.5, 1.5, -5.0, 0.0f, 0.0f, 1.0f,
        -1.0, 0.5, -5.0, 0.0f, 0.0f, 1.0f
};

//static GLfloat vertexs[] = {
//        2.0/5.0f, 0.0, -2.0/5.0f,
//        0.0, 2.0/5.0f, -2.0/5.0f,
//        -2.0/5.0f, 0.0, -2.0/5.0f
////        3.5, -1.0, -5.0,
////        2.5, 1.5, -5.0,
////        -1.0, 0.5, -5.0
//};

static GLuint ind[] = {

        3, 4, 5,
        0, 1, 2
};

void PerspactiveTransformDemo::onDraw() {
    //由于openGL看像屏幕方向是 -z轴，因此定义坐标的时候 -2，-5； 会显示-2的颜色。
    //但是vertexs经过mvp矩阵转换，最终z是正值；所以深度缓存判断z越大则颜色被替换
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, nullptr);
}

void PerspactiveTransformDemo::onSurfaceCreated() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f,0.0f,0.0f,1.0f);
    m_ProgramObj = GLUtils::createProgram(&this->VERTEX_SHADER,&this->FRAGMENT_SHADER);
    if(m_ProgramObj == 0){
        LOGI(TAG_PERSPACTIVE_TRANSFORM_DEMO,"create program error");
        return;
    }
    glUseProgram(m_ProgramObj);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertexs),vertexs,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(ind),ind,GL_STATIC_DRAW);

    glVertexAttribPointer(DEFAULT_POS_LOCATION,3,GL_FLOAT,GL_FALSE, 6*sizeof(float ), nullptr);
    glEnableVertexAttribArray(DEFAULT_POS_LOCATION);

    glVertexAttribPointer(DEFAULT_COLOR_LOCATION,3,GL_FLOAT,GL_FALSE,6*sizeof(float ),(void*)(3* sizeof(float)));
    glEnableVertexAttribArray(DEFAULT_COLOR_LOCATION);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    view = glm::translate(view,glm::vec3(0.0f,0.0f,-5.0f));
    //这里的zNear和zFar传正的，表示近平面和远平面的距离。
    projection = glm::perspective(glm::radians(90.0f),1.0f,2.1f,5.5f);
    glm::mat4 value = projection * view * model;



    glm::vec4 result = value*glm::vec4(2.0, 0.0, -2.0,1.0);
    LOGI(TAG_PERSPACTIVE_TRANSFORM_DEMO,"%f,%f,%f,%f",result.x,result.y,result.z,result.w);
   glm::vec4 result1 = value*glm::vec4(0.0, 2.0, -2.0,1.0);
    LOGI(TAG_PERSPACTIVE_TRANSFORM_DEMO,"%f,%f,%f,%f",result1.x,result1.y,result1.z,result1.w);
  glm::vec4 result2 = value*glm::vec4(-2.0, 0.0, -2.0,1.0);
    LOGI(TAG_PERSPACTIVE_TRANSFORM_DEMO,"%f,%f,%f,%f",result2.x,result2.y,result2.z,result2.w);

    glm::vec4 result3 = value*glm::vec4(3.5, -1.0, -5.0,1.0);
    LOGI(TAG_PERSPACTIVE_TRANSFORM_DEMO,"%f,%f,%f,%f",result3.x,result3.y,result3.z,result3.w);
    glm::vec4 result4 = value*glm::vec4(2.5, 1.5, -5.0,1.0);
    LOGI(TAG_PERSPACTIVE_TRANSFORM_DEMO,"%f,%f,%f,%f",result4.x,result4.y,result4.z,result4.w);
    glm::vec4 result5 = value*glm::vec4(-1.0, 0.5, -5.0,1.0);
    LOGI(TAG_PERSPACTIVE_TRANSFORM_DEMO,"%f,%f,%f,%f",result5.x,result5.y,result5.z,result5.w);

    //PerspactiveTransformDemo: 2.000000,0.000000,6.813814,7.000000
   //PerspactiveTransformDemo: 0.000000,2.000000,6.813814,7.000000
   //PerspactiveTransformDemo: -2.000000,0.000000,6.813814,7.000000




    glUniformMatrix4fv(glGetUniformLocation(m_ProgramObj,"transform"),1,GL_FALSE,glm::value_ptr(value));
}
