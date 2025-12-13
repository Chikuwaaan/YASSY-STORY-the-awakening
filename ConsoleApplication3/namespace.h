#include <SDL.h>

#pragma once

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