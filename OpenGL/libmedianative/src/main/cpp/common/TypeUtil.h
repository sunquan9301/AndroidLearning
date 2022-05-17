//
// Created by 孙全 on 2022/5/17.
//
#pragma once

#include <string>

using namespace std;
#ifdef __cplusplus
extern "C" {
#endif
#include <jni.h>


#ifdef __cplusplus
}
#endif

std::string JNI_GetString(JNIEnv *env, jstring j_string);


