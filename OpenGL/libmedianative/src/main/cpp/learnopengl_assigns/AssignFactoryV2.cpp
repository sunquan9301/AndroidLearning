//
// Created by 孙全 on 2022/5/22.
//

#include "AssignFactoryV2.h"
AssignFactoryV2 *AssignFactoryV2::m_Instance = new AssignFactoryV2();


AssignFactoryV2 *AssignFactoryV2::getInstance() {
    return m_Instance;
}

void AssignFactoryV2::createAssignDemo(int type) {
    this->p_AssignDemo = new SimpleShaderV2();
}
