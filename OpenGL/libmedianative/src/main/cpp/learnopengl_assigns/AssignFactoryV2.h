//
// Created by 孙全 on 2022/5/22.
//
#pragma once
#include "common/LogFun.h"
#include "common/AssignType.h"
#include "learnopengl_assigns/GLAbsRenderV2.h"
#include "AssignFactory.h"
//shaders
#include "learnopengl_assigns/shaders/SimpleShaderV2.h"


class AssignFactoryV2 {
public:
    void createAssignDemo(int type);
    void onInit(JNIEnv *env,jobject asset_manager){
        if(!p_AssignDemo){
            LOGE(TAG_ASSIGN_FACTORY_V2,"p_AssignDemo is null");
            return;
        }
        p_AssignDemo->onInit(env,asset_manager);
    }
    void onDraw(){
        if(!p_AssignDemo){
            LOGE(TAG_ASSIGN_FACTORY_V2,"p_AssignDemo is null");
            return;
        }
        p_AssignDemo->onDraw();
    }
    void onSurfaceCreated(){
        if(!p_AssignDemo){
            LOGE(TAG_ASSIGN_FACTORY_V2,"p_AssignDemo is null");
            return;
        }
        p_AssignDemo->onSurfaceCreated();
    }
    void onSurfaceChange(int width,int height){
        if(!p_AssignDemo){
            LOGE(TAG_ASSIGN_FACTORY_V2,"p_AssignDemo is null");
            return;
        }
        p_AssignDemo->onSurfaceChange(width,height);
    }
    void onDestroy(){
        if(!p_AssignDemo){
            LOGE(TAG_ASSIGN_FACTORY_V2,"p_AssignDemo is null");
            return;
        }
        p_AssignDemo->onDestroy();
    }
    static AssignFactoryV2 *getInstance();

private:
    static AssignFactoryV2 *m_Instance;
    GLAbsRenderV2* p_AssignDemo;
};


