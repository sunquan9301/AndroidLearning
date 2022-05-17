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
    LOGD(TAG_ASSET,"numByte: %d, len: %d", numByte, len);
    AAsset_close(pAsset);
    return pBuffer;
}
