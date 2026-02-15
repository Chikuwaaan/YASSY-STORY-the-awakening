#pragma once

#include <SDL.h>

struct MOUSE {
    int x;
    int y;
    bool left;
    bool middle;
    bool right;
};

struct EVENT {
    bool ESCAPE;
    bool DEL;
    bool F12;
    bool RETURN;
    bool SPACE;
    bool Q;
    bool E;
    bool Up;
    bool Down;
    bool Left;
    bool Right;
    int MouseWheel;
    bool MouseLeft;
    bool MouseMiddle;
    bool MouseRight;
    bool MouseX1;
    bool MouseX2;
};

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

