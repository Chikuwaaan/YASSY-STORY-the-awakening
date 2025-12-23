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

namespace utilities {
    bool HitDetection(OBJRECT obj1, OBJRECT obj2) {
        double x1 = obj1.x;
        double y1 = obj1.y;
        double w1 = obj1.w;
        double h1 = obj1.h;
        double x2 = obj2.x;
        double y2 = obj2.y;
        double w2 = obj2.w;
        double h2 = obj2.h;
        return (x1 - 0.5 * w1 < x2 + 0.5 * w2 &&
            x1 + 0.5 * w1 > x2 - 0.5 * w2 &&
            y1 - 0.5 * h1 < y2 + 0.5 * h2 &&
            y1 + 0.5 * h1 > y2 - 0.5 * h2);
    }
}

namespace platformer {
    double gravity = -2000.0;
    int flames = 0;
}

