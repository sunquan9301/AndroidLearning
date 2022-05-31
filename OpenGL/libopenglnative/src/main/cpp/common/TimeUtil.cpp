//
// Created by 孙全 on 2022/5/28.
//

#include "TimeUtil.h"

string TimeUtil::getLocalTime() {
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    return tmp;
}

long TimeUtil::getTime() {
    time_t timep;
    time(&timep);
    return timep;
}