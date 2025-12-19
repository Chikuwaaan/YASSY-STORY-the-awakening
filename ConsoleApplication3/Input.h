#pragma once

#include "SDL.h"
#include "structs.h"

class Input
{
public:
    const Uint8* keystate;
    EVENT event;
    void GetKey();
};

