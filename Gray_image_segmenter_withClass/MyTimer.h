#pragma once
#include <windows.h>

//计时类
class MyTimer {
private:
    int _freq;
    LARGE_INTEGER _begin;
    LARGE_INTEGER _end;
public:
    long costTime;            // 花费的时间(精确到微秒)
public:
    MyTimer() {
        LARGE_INTEGER tmp;
        QueryPerformanceFrequency(&tmp);
        _freq = tmp.QuadPart;
        costTime = 0;
    }
    void Start() {            // 开始计时
        QueryPerformanceCounter(&_begin);
    }
    void End() {                // 结束计时
        QueryPerformanceCounter(&_end);
        costTime = (long)((_end.QuadPart - _begin.QuadPart) * 1000 / _freq);
    }
    void Reset() {            // 计时清0
        costTime = 0;
    }
};
