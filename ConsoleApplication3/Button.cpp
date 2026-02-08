#include "Button.h"
#include "Textures.h"
#include "Input.h"
#include "structs.h"
#include "iconProperty.h"
#include "Sounds.h"

Textures* Button::texturesP = nullptr;
Input* Button::inputP = nullptr;
Sounds* Button::soundsP = nullptr;

Button::Button(int X, int Y, int W, int H) {
    x = X;
    y = Y;
    w = W;
    h = H;
    color = { 0,0,0,255 };
    state = State::Invisible;

    icon = Icons::Null;
}

void Button::Draw() {
    if (state != State::Invisible) {
        OBJRECT dst = { (double)x,(double)y,(double)w,(double)h,1 };
        texturesP->DrawImage("button16", dst, 0, {});
        //texturesP->DrawRect(color, dst, 0);
        SDL_Rect dstS = { x,y,w,h };
        texturesP->DrawIcon(icon, dstS);
    }
}

bool Button::OnMouse() {
    MOUSE mouse = inputP->mouse;

    OBJRECT cursor;
    cursor = { (double)mouse.x,(double)mouse.y,0,0 };
    OBJRECT rect;
    rect = { (double)x,(double)y, (double)w, (double)h };

    return utilities::HitDetectionEquals(cursor, rect);
}

bool Button::CheckPressed() {
    bool on = OnMouse();
    if (on) {
        color = { 0,255,0,255 };
    }
    else {
        color = { 255,0,0,255 };
    }

    if (on && state == State::Available) {
        if (inputP->event.MouseLeft) {
            soundsP->PlaySE("pochi");
            if (action) {
                action();
                return 1;
            }
        }
    }
    return 0;
}