#include "Button.h"
#include "Textures.h"
#include "Input.h"
#include "structs.h"

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
    OBJRECT dst = { (double)x - w/2,(double)y - h/2,(double)w,(double)h,1 };
    texturesP->DrawRect(color, dst, 0);
}

bool Button::OnMouse() {
    MOUSE mouse = inputP->mouse;

    OBJRECT cursor;
    cursor = { (double)mouse.x,settings::baseH-(double)mouse.y,0,0 };
    OBJRECT rect;
    rect = { (double)x,(double)y, (double)w, (double)h };

    return utilities::HitDetection(cursor, rect);
}

void Button::CheckPressed() {
    bool on = OnMouse();
    if (on) {
        color = { 0,0,255,255 };
    }
    else {
        color = { 255,0,0,255 };
    }

    if (on) {
        if (inputP->event.MouseLeft) {
            if (action) {
                action();
            }
        }
    }
}