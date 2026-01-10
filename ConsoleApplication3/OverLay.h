#pragma once
#include <SDL.h>

class Textures;

struct PINHOLE {
    bool effect;
    float radius;
    float shrinkSpeed;
    SDL_Color color;
};

class OverLay
{
private:
    PINHOLE pinHole;
public:
    static Textures* texturesP;
    OverLay();
    void Update();

    void PinHole();
};

