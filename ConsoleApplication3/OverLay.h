#pragma once
#include <SDL.h>

class Textures;
class Player;

struct PINHOLE {
    bool effect;
    double radius;
    double shrinkSpeed;
    double waitTime;
    SDL_Color color;
};
struct FADE {
    int effect;
    double speed;
    double time;
    SDL_Color color;
};

class OverLay
{
private:
    PINHOLE pinHole;
    FADE fade;
public:
    static Textures* texturesP;
    static Player* playerP;
    OverLay();
    void Update();

    void PinHole(double radius, double shrinkSpeed, double waitTime, SDL_Color color);
    void FadeOut(double speed, SDL_Color color);
    void FadeIn(double speed, SDL_Color color);
};

