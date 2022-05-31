//
// Created by 孙全 on 2022/5/17.
//

#include "AssetFun.h"

char *AssetFun::readAssetFile(const char *filename, AAssetManager *mgr) {
    if (mgr == NULL) {
        LOGE(TAG_ASSET,"pAssetManager is null!");
        return NULL;
    }
    AAsset *pAsset = AAssetManager_open(mgr, filename, AASSET_MODE_UNKNOWN);
    off_t len = AAsset_getLength(pAsset);
    char *pBuffer = (char *) malloc(len + 1);
    pBuffer[len] = '\0';
    int numByte = AAsset_read(pAsset, pBuffer, len);
    LOGD(TAG_ASSET,"numByte: %d, len: %ld", numByte, len);
    AAsset_close(pAsset);
    return pBuffer;
}

char *AssetFun::openTextFile(const char *path,AAssetManager *mgr) {
    char *buffer;
    AAsset *asset = AAssetManager_open(mgr, path, AASSET_MODE_UNKNOWN);
    if (asset == nullptr) {
        return nullptr;
    }
    off_t length = AAsset_getLength(asset);
    buffer = new char[length + 1];
    int num = AAsset_read(asset, buffer, length);
    AAsset_close(asset);
    if (num != length) {
        delete[] buffer;
        return nullptr;
    }
    buffer[length] = '\0';
    return buffer;
}
