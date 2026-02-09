#pragma once

#include "UIElement.h"
#include "iconProperty.h"
#include <functional>
#include <SDL.h>

class Textures;
class Input;
class Sounds;

enum class State {
    Idle,
    OnMouse,
    Pressed,
    Unavailable
};

class Button
{
private:
    SDL_Color color;
    
public:
    int x, y, w, h;
    State state;
    std::function<void()> action;
    Icons icon;
    bool visible;

    static Textures* texturesP;
    static Input* inputP;
    static Sounds* soundsP;

    Button(int X, int Y, int W, int H);
    void Draw();
    bool CheckOnMouse();
    bool CheckPressed();
};

