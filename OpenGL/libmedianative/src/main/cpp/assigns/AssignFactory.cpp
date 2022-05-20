//
// Created by 孙全 on 2022/5/20.
//

#include "AssignFactory.h"
AssignFactory *AssignFactory::m_Instance = new AssignFactory();


AssignFactory *AssignFactory::getInstance() {
    return m_Instance;
}
void AssignFactory::createAssignDemo(int type) {
    if(type == ASSIGN_LEARN_OPENGL_TRIANGLE_SIMPLE){
        this->p_AssignDemo = new RenderTriangle();
        return;
    }
    if(type == ASSIGN_LEARN_OPENGL_TRIANGLE_SIMPLE_VBO){
        this->p_AssignDemo = new RenderTriangleVBO();
        return;
    }
    this->p_AssignDemo = new RenderTriangle();
}