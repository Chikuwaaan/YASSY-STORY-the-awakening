#pragma once
#include <SDL.h>
class Timer
{
private:
    Uint32 last;
    Uint32 now;
    Uint32 delta;
    double timer;
public:
    Timer();
    void Update();
    void Reset();
    double GetTime();
};

