#pragma once

#include <SDL.h>
#include "structs.h"

namespace settings {
	extern double maxFps;
	extern double dt;
    extern double multiplier;
    extern double timeScale;
    extern int baseW;
    extern int baseH;
    extern SDL_Window* window;
    extern SDL_Renderer* renderer;
}

namespace utilities {
    bool HitDetection(OBJRECT obj1, OBJRECT obj2);
    SDL_Color HSVtoRGB(double h, double s, double v, int a);
}

namespace platformer {
    extern int level;
    extern double gravity;
    extern int flames;
}

