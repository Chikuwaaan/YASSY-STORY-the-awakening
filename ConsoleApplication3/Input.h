#pragma once

#include "SDL.h"

class Input
{
public:
    const Uint8* keystate;
    void GetKey();
};

