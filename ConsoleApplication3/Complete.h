#pragma once

#include "Timer.h"

class Textures;

class Complete
{
private:
    Timer timer;

    double clearTime;
public:
    static Textures* texturesP;

    Complete();
    void Update();
    void SetClearTime(double time);
};

