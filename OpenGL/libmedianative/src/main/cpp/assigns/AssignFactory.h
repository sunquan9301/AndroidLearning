//
// Created by 孙全 on 2022/5/20.
//

#ifndef OPENGL_ASSIGNFACTORY_H
#define OPENGL_ASSIGNFACTORY_H
#pragma once

#include "assigns/GLAbsRender.h"
#include "common/LogFun.h"
#include "common/AssignType.h"

#include "assigns/triangle/RenderTriangle.h"
#include "assigns/triangle/RenderTriangleVBO.h"
#include "assigns/triangle/RenderTriangleVAO.h"
#include "assigns/triangle/RenderRect.h"
#include "assigns/triangle/RenderRectTwoFragmentShader.h"
#include "assigns/triangle/RenderRectEBO.h"

class AssignFactory {
public:
    void createAssignDemo(int type);
    void onInit(JNIEnv *env,jobject asset_manager,const string &vertexShaderAssetName,const string &fragmentShaderAssetName){
        if(!p_AssignDemo){
            LOGE(TAG_ASSIGN_FACTORY,"p_AssignDemo is null");
            return;
        }
        p_AssignDemo->onInit(env,asset_manager,vertexShaderAssetName,fragmentShaderAssetName);
    }
    void onDraw(){
        if(!p_AssignDemo){
            LOGE(TAG_ASSIGN_FACTORY,"p_AssignDemo is null");
            return;
        }
        p_AssignDemo->onDraw();
    }
    void onSurfaceCreated(){
        if(!p_AssignDemo){
            LOGE(TAG_ASSIGN_FACTORY,"p_AssignDemo is null");
            return;
        }
        p_AssignDemo->onSurfaceCreated();
    }
    void onSurfaceChange(int width,int height){
        if(!p_AssignDemo){
            LOGE(TAG_ASSIGN_FACTORY,"p_AssignDemo is null");
            return;
        }
        p_AssignDemo->onSurfaceChange(width,height);
    }
    void onDestroy(){
        if(!p_AssignDemo){
            LOGE(TAG_ASSIGN_FACTORY,"p_AssignDemo is null");
            return;
        }
        p_AssignDemo->onDestroy();
    }

    static AssignFactory *getInstance();

private:
    static AssignFactory *m_Instance;
    GLAbsRender* p_AssignDemo;
};


#endif //OPENGL_ASSIGNFACTORY_H
