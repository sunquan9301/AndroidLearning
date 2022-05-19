//
// Created by 孙全 on 2022/5/17.
//
#include <TypeUtil.h>

extern "C"
{
}
string JNI_GetString(JNIEnv *env, jstring j_string) {
    const char *c_str = j_string == nullptr ? "" : env->GetStringUTFChars(j_string, nullptr);
    string cppStr = c_str;
    if (j_string) env->ReleaseStringUTFChars(j_string, c_str);
    return cppStr;
}
