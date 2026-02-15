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
    isSelected = 0;

    icon = Icons::Null;
    visible = 1;
    text = "";
}

void Button::Draw() {
    if (w == 0 || h == 0) return;
    if (visible) {
        bool wide = 0;
        if (w / h != 1) {
            wide = 1;
        }
        //texturesP->DrawImage("assy", { (double)x, (double)y, (double)w, (double)h }, 0, {});
        if (wide) {
            Icons buttonL = Icons::Null;
            Icons buttonR = Icons::Null;
            Icons buttonM = Icons::Null;
            if (state == State::Idle) {
                buttonL = Icons::ButtonLIdle;
                buttonR = Icons::ButtonRIdle;
                buttonM = Icons::ButtonMIdle;
            }
            else if (state == State::OnMouse) {
                buttonL = Icons::ButtonLOnMouse;
                buttonR = Icons::ButtonROnMouse;
                buttonM = Icons::ButtonMOnMouse;
            }
            else if (state == State::Pressed) {
                buttonL = Icons::ButtonLPressed;
                buttonR = Icons::ButtonRPressed;
                buttonM = Icons::ButtonMPressed;
            }
            else if (state == State::Unavailable) {
                buttonL = Icons::ButtonLUnavailable;
                buttonR = Icons::ButtonRUnavailable;
                buttonM = Icons::ButtonMUnavailable;
            }

            double a = ((w / h) - 1) / 2.0;
            int xL = (int)(x - a * h);
            int xR = (int)(x + a * h);
            SDL_Rect dstL = { xL,y,h,h };
            SDL_Rect dstR = { xR,y,h,h };
            SDL_Rect dstM;
            dstM.x = x;
            dstM.y = y;
            dstM.w = dstR.x - dstL.x;
            dstM.h = h,
            texturesP->DrawIcon(buttonL, dstL);
            texturesP->DrawIcon(buttonR, dstR);
            texturesP->DrawIcon(buttonM, dstM);
            texturesP->DrawIcon(icon, {x,y,h,h});
            if (text != "") {
                SDL_Color white = { 100,200,255 };
                SDL_Color black = { 0,73,220,255 };
                OBJRECT dstT = { (double)x, (double)y, 1,1 };
                texturesP->DrawTexts(text, white, black, dstT, 0, Anchor::Center);
            }

            if (isSelected) {
                dstR.x = dstR.x + h / 8;
                dstR.y = dstR.y + h / 8;
                texturesP->DrawIcon(Icons::UICursor1, dstR);
                dstR.y = dstR.y - h / 4;
                texturesP->DrawIcon(Icons::UICursor4, dstR);

                dstL.x = dstL.x - h / 8;
                dstL.y = dstL.y + h / 8;
                texturesP->DrawIcon(Icons::UICursor2, dstL);
                dstL.y = dstL.y - h / 4;
                texturesP->DrawIcon(Icons::UICursor3, dstL);
            }
        }
        else {
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
            texturesP->DrawIcon(button, {x,y,w,h});
            texturesP->DrawIcon(icon, { x,y,h,h });

            if (isSelected) {
                texturesP->DrawIcon(Icons::UICursor1, { x+w/8,y+h/8,w,h });
                texturesP->DrawIcon(Icons::UICursor2, { x-w/8,y+h/8,w,h });
                texturesP->DrawIcon(Icons::UICursor3, { x-w/8,y-h/8,w,h });
                texturesP->DrawIcon(Icons::UICursor4, { x+w/8,y-h/8,w,h });
            }
        }
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

    if (isSelected && state != State::Unavailable && visible) {
        if (inputP->event.SPACE) {
            soundsP->PlaySE("pochi");

            if (action) {
                action();
                return 1;
            }
        }
    }

    return 0;
}