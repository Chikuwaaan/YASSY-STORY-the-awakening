#pragma once

#include "SDL.h"
#include "structs.h"
#include <SDL.h>

class Input
{
public:
    const Uint8* keystate;
    EVENT event;
    MOUSE mouse;
    void GetKey();
    void GetCursor();
    void GetEvent();
    
};

