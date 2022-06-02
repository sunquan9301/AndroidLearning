//
// Created by 孙全 on 2022/5/17.
//

#pragma once

#ifndef OPENGL_ASSETFUN_H
#define OPENGL_ASSETFUN_H
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <common/LogFun.h>

class AssetFun {

public:
    static char *readAssetFile(const char *filename, AAssetManager *mgr);
    static char *openTextFile(const char *filename, AAssetManager *mgr);

    static unsigned char *loadImageToMemory(const char *filename, AAssetManager *mgr, int *len);
};


#endif //OPENGL_ASSETFUN_H
