#include "namespace.h"
#include <cmath>

namespace settings {
    double maxFps = 120.0;
    double dt = 1.0 / maxFps;
    double multiplier = 1;
    double timeScale = dt * multiplier;
    int baseW = 1920;
    int baseH = 1080;
    int winW = 0;
    int winH = 0;
    SDL_Window* window;
    SDL_Renderer* renderer;
    int BGM = 0;
    int SE = 16;
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

        if (!(w1 && h1 && w2 && h2)) return 0;

        return (x1 - 0.5 * w1 < x2 + 0.5 * w2 &&
            x1 + 0.5 * w1 > x2 - 0.5 * w2 &&
            y1 - 0.5 * h1 < y2 + 0.5 * h2 &&
            y1 + 0.5 * h1 > y2 - 0.5 * h2);
    }

    bool HitDetectionEquals(OBJRECT obj1, OBJRECT obj2) {
        double x1 = obj1.x;
        double y1 = obj1.y;
        double w1 = obj1.w;
        double h1 = obj1.h;
        double x2 = obj2.x;
        double y2 = obj2.y;
        double w2 = obj2.w;
        double h2 = obj2.h;
        return (x1 - 0.5 * w1 <= x2 + 0.5 * w2 &&
            x1 + 0.5 * w1 >= x2 - 0.5 * w2 &&
            y1 - 0.5 * h1 <= y2 + 0.5 * h2 &&
            y1 + 0.5 * h1 >= y2 - 0.5 * h2);
    }

    SDL_Color HSVtoRGB(double h, double s, double v, int a) {
        SDL_Color rgb;

        double c = v * s;
        double h_ = h / 60.0f;
        double x = c * (1 - std::fabs(fmod(h_, 2.0f) - 1));

        double r1 = 0, g1 = 0, b1 = 0;

        if (0 <= h_ && h_ < 1) { r1 = c; g1 = x; }
        else if (1 <= h_ && h_ < 2) { r1 = x; g1 = c; }
        else if (2 <= h_ && h_ < 3) { g1 = c; b1 = x; }
        else if (3 <= h_ && h_ < 4) { g1 = x; b1 = c; }
        else if (4 <= h_ && h_ < 5) { r1 = x; b1 = c; }
        else if (5 <= h_ && h_ < 6) { r1 = c; b1 = x; }

        double m = v - c;

        rgb.r = static_cast<int>((r1 + m) * 255);
        rgb.g = static_cast<int>((g1 + m) * 255);
        rgb.b = static_cast<int>((b1 + m) * 255);
        rgb.a = a;

        return rgb;
    }

    double DegreetoRadian(double angle) {
        return angle / 180 * acos(-1);
    }

    double DistanceSQ(double x1, double y1, double x2, double y2) {
        double dx = x2 - x1;
        double dy = y2 - y1;
        return dx * dx + dy * dy;
    }
}

namespace platformer {
    double gravity = -2150.0;
    int flames = 0;
    int level = 1;
}

namespace savedata {
    InputType Up = { InputDevice::Keyboard, SDL_SCANCODE_W, 0 };
    InputType Down = { InputDevice::Keyboard, SDL_SCANCODE_S, 0 };
    InputType Left = { InputDevice::Keyboard, SDL_SCANCODE_A, 0 };
    InputType Right = { InputDevice::Keyboard, SDL_SCANCODE_D, 0 };
    InputType Jump = { InputDevice::Keyboard, SDL_SCANCODE_M, 0 };
    InputType Dash = { InputDevice::Keyboard, SDL_SCANCODE_N, 0 };
    bool InvertDash;

    std::vector<std::vector<bool>> coin = {
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0}
    };
}
