#pragma once

#include "SDL.h"
#include "structs.h"
#include <SDL.h>

class Input
{
public:
    const Uint8* keystate;
    SDL_Event event;
    void GetKey();
};

