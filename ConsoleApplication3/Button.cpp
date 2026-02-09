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
    state = State::Unavailable;

    icon = Icons::Null;
    visible = 0;
}

void Button::Draw() {
    if (visible) {
        SDL_Rect dst = { x,y,w,h };
        Icons button = Icons::Null;

        if (state == State::Idle) {
            button = Icons::ButtonIdle;
        }
        else if (state == State::OnMouse) {
            button = Icons::ButtonOnMouse;
        }
        else if (state == State::Pressed) {
            button = Icons::ButtonPressed;
        }
        else if (state == State::Unavailable) {
            button = Icons::ButtonUnavailable;
        }

        texturesP->DrawIcon(button, dst);
        texturesP->DrawIcon(icon, dst);
    }
}

bool Button::CheckOnMouse() {
    if (state == State::Idle) {
        MOUSE mouse = inputP->mouse;
        OBJRECT cursor;
        cursor = { (double)mouse.x,(double)mouse.y,0,0 };
        OBJRECT rect;
        rect = { (double)x,(double)y, (double)w, (double)h };
        if (utilities::HitDetectionEquals(cursor, rect)) {
            state = State::OnMouse;
            return 1;
        }
    }
    
    return 0;
}

bool Button::CheckPressed() {
    if (state == State::OnMouse && visible) {
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