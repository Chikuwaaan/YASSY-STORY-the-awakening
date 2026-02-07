#pragma once

#include "structs.h"
#include <SDL.h>

class Input
{
private:
    bool isAnyKeyPressed;
    
public:
    const Uint8* keystate;
    EVENT event;
    MOUSE mouse;
    void GetCursor();
    void GetKey();
    void GetEvent();
   
    bool IsAnyKeyPressed();
};

