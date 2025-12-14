#pragma once

#include <SDL.h>
#include "structs.h"

namespace settings {
	extern double maxFps;
	extern double dt;
    extern double timeMultiplier;
    extern double timeScale;
    extern int baseW;
    extern int baseH;
    extern SDL_Window* window;
    extern SDL_Renderer* renderer;
}

namespace utilities {
    extern bool HitDetection(OBJRECT obj1, OBJRECT obj2);
}