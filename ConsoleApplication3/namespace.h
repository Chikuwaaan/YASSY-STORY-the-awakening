#pragma once

#include <SDL.h>
#include "structs.h"
#include "Input.h"

namespace settings {
    extern double maxFps;
    extern double dt;
    extern double multiplier;
    extern double timeScale;
    extern int baseW;
    extern int baseH;
    extern int winW;
    extern int winH;
    extern SDL_Window* window;
    extern SDL_Renderer* renderer;
    extern int BGM;
    extern int SE;
}

namespace utilities {
    bool HitDetection(OBJRECT obj1, OBJRECT obj2);
    bool HitDetectionEquals(OBJRECT obj1, OBJRECT obj2);
    SDL_Color HSVtoRGB(double h, double s, double v, int a);
    double DegreetoRadian(double angle);
    double DistanceSQ(double x1, double y1, double x2, double y2);
}

namespace platformer {
    extern double gravity;
    extern int flames;

    extern int level;
    extern int CP;
    extern int coin[3];
    extern double time;
    extern int death;
}

namespace savedata {
    extern int slot;
    extern bool InvertDash;
    extern bool Blur;
    extern bool Eye;
    extern bool Tomato;
    extern bool une;
    extern bool dev;

    extern std::vector<std::vector<int>> coin;
    extern std::vector<int> completedLevel;
    extern std::vector<double> time;
}
