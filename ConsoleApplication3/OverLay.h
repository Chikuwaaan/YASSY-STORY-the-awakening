#pragma once
#include <SDL.h>

class Textures;
class Player;

struct PINHOLE {
    int x;
    int y;
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
    OverLay();
    
    void Update();

    void PinHole(int x, int y,double radius, double shrinkSpeed, double waitTime, SDL_Color color);
    void FadeOut(double speed, SDL_Color color);
    void FadeIn(double speed, SDL_Color color);
    
};

