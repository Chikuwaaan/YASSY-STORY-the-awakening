#include "namespace.h"

namespace settings {
    double maxFps = 120.0;
    double dt = 1.0 / maxFps;
    double timeMultiplier = 1.0;
    double timeScale = dt * timeMultiplier;
    int baseW = 1920;
    int baseH = 1080;
    SDL_Window* window;
    SDL_Renderer* renderer;
}