#pragma once

#include "UIElement.h"
#include <functional>

class Textures;

class Button
{
private:
    int x, y, w, h;
public:
    std::function<void()> action;
    static Textures* texturesP;

    Button(int X, int Y, int W, int H);
    void Draw();
};

