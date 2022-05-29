//
// Created by 孙全 on 2022/5/28.
//

#ifndef OPENGL_TIMEUTIL_H
#define OPENGL_TIMEUTIL_H


#include <stdio.h>
#include <string>

using namespace std;

class TimeUtil final {
public:
    static string getLocalTime();
    static long getTime();
};
#endif //OPENGL_TIMEUTIL_H
