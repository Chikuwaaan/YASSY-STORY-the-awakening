#pragma once

#include "UIElement.h"
#include "iconProperty.h"
#include <functional>
#include <SDL.h>

class Textures;
class Input;
class Sounds;

enum class State {
    Available,
    Unavailable,
    Invisible,
    Pressed
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

    static Textures* texturesP;
    static Input* inputP;
    static Sounds* soundsP;

    Button(int X, int Y, int W, int H);
    void Draw();
    bool OnMouse();
    bool CheckPressed();
};

