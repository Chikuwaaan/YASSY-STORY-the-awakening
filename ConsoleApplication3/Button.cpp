#include "Button.h"
#include "Textures.h"

Textures* Button::texturesP = nullptr;

Button::Button(int X, int Y, int W, int H) {
    x = X;
    y = Y;
    w = W;
    h = H;
}

void Button::Draw() {
    SDL_Color color = { 0,0,0,255 };
    OBJRECT dst = { (double)x,(double)y,(double)w,(double)h,0 };
    texturesP->DrawRect(color, dst, 0);
}