#pragma once

#include "UIElement.h"
#include <functional>
#include <SDL.h>

class Textures;
class Input;

class Button
{
private:
    int x, y, w, h;
    SDL_Color color;
public:
    std::function<void()> action;
    static Textures* texturesP;
    static Input* inputP;

    Button(int X, int Y, int W, int H);
    void Draw();
    bool OnMouse();
    bool CheckPressed();
};

