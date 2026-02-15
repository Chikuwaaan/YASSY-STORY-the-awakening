#include "Input.h"
#include "namespace.h"
#include <iostream>

void Input::GetCursor() {
    int x, y;
    Uint32 buttons = SDL_GetMouseState(&x, &y);
    mouse.x = (int)round(x * settings::baseW / settings::winW);
    mouse.y = settings::baseH - (int)round(y * settings::baseH / settings::winH) - 1;

    if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        mouse.left = 1;
    }
    else {
        mouse.left = 0;
    }
    if (buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
        mouse.middle = 1;
    }
    else {
        mouse.middle = 0;
    }
    if (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
        mouse.right = 1;
    }
    else {
        mouse.right = 0;
    }
}

void Input::GetKey() {
    keystate = SDL_GetKeyboardState(NULL);
}

void Input::GetEvent() {
    isAnyKeyPressed = 0;
    event = {};

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            isAnyKeyPressed = 1;
            if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                event.ESCAPE = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_DELETE) {
                event.DEL = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_F12) {
                event.F12 = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                event.RETURN = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                event.SPACE = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_Q) {
                event.Q = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_E) {
                event.E = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_W) {
                event.Up = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_S) {
                event.Down = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_A) {
                event.Left = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_D) {
                event.Right = 1;
            }
        }

        if (e.type == SDL_MOUSEWHEEL) {
            event.MouseWheel = e.wheel.y;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            if (e.button.button == SDL_BUTTON_LEFT) {
                event.MouseLeft = 1;
            }
            if (e.button.button == SDL_BUTTON_MIDDLE) {
                event.MouseMiddle = 1;
            }
            if (e.button.button == SDL_BUTTON_RIGHT) {
                event.MouseRight = 1;
            }
            if (e.button.button == SDL_BUTTON_X1) {
                event.MouseX1 = 1;
            }
            if (e.button.button == SDL_BUTTON_X2) {
                event.MouseX2 = 1;
            }
        }
    }
}

bool Input::IsAnyKeyPressed() {
    return isAnyKeyPressed;
}