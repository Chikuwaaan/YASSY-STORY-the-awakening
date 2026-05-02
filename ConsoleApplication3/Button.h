#pragma once

#include <string>
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
public:
    int x, y, w, h;
    State state;
    bool isSelected;
    std::function<void()> action;
    Icons icon;
    std::string texName;
    std::string text;
    bool visible;
    bool alpha;

    SDL_Color color1;
    SDL_Color color2;
    double textSize;

    static Textures* texturesP;
    static Input* inputP;
    static Sounds* soundsP;

    Button(int X, int Y, int W, int H);
    void Draw();
    bool CheckOnMouse();
    bool CheckPressed();
};

