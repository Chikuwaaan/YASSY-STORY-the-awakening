#include "Input.h"
#include "namespace.h"
#include <iostream>

void Input::GetKey() {
    keystate = SDL_GetKeyboardState(NULL);
}

void Input::GetCursor() {
    int x, y;
    Uint32 buttons = SDL_GetMouseState(&x, &y);
    mouse.x = x;
    mouse.y = settings::baseH - y - 1;
    std::cout << mouse.x << "," << mouse.y << std::endl;

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

void Input::GetEvent() {
    event.ESCAPE = 0;
    event.DEL = 0;
    event.F12 = 0;
    event.Q = 0;
    event.E = 0;
    event.MouseWheel = 0;
    event.MouseLeft = 0;
    event.MouseMiddle = 0;
    event.MouseRight = 0;
    event.MouseX1 = 0;
    event.MouseX2 = 0;

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                event.ESCAPE = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_DELETE) {
                event.DEL = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_F12) {
                event.F12 = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_Q) {
                event.Q = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_E) {
                event.E = 1;
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

