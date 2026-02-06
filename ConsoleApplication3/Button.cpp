#include "Button.h"
#include "Textures.h"
#include "Input.h"
#include "structs.h"
#include "iconProperty.h"

Textures* Button::texturesP = nullptr;
Input* Button::inputP = nullptr;

Button::Button(int X, int Y, int W, int H) {
    x = X;
    y = Y;
    w = W;
    h = H;
    color = { 0,0,0,255 };
}

void Button::Draw() {
    OBJRECT dst = { (double)x,(double)y,(double)w,(double)h,1 };
    texturesP->DrawRect(color, dst, 0);
    SDL_Rect dstS = { x,y,w,h };
    texturesP->DrawIcon(Icons::uo, dstS);
}

bool Button::OnMouse() {
    MOUSE mouse = inputP->mouse;

    OBJRECT cursor;
    cursor = { (double)mouse.x,(double)mouse.y,0,0 };
    OBJRECT rect;
    rect = { (double)x,(double)y, (double)w, (double)h };

    return utilities::HitDetectionEquals(cursor, rect);
}

void Button::CheckPressed() {
    bool on = OnMouse();
    if (on) {
        color = { 150,150,150,255 };
    }
    else {
        color = { 200,200,200,255 };
    }

    if (on) {
        if (inputP->event.MouseLeft) {
            if (action) {
                action();
            }
        }
    }
}