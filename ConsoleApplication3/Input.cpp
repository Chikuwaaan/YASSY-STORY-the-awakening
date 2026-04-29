#include "Input.h"
#include "namespace.h"
#include <iostream>

Input::Input() {
    config = {
        {Action::HoldUp, {InputDevice::Keyboard, SDL_SCANCODE_W, 0}},
        {Action::HoldDown, {InputDevice::Keyboard, SDL_SCANCODE_S, 0}},
        {Action::HoldLeft, {InputDevice::Keyboard, SDL_SCANCODE_A, 0}},
        {Action::HoldRight, {InputDevice::Keyboard, SDL_SCANCODE_D, 0}},
        {Action::HoldJump, {InputDevice::Keyboard, SDL_SCANCODE_M, 0}},
        {Action::HoldRun, {InputDevice::Keyboard, SDL_SCANCODE_N, 0}}
    };
    eventConfig = {
        {Event::Confirm, {InputDevice::Keyboard, SDL_SCANCODE_SPACE, 0}},
        {Event::Back, {InputDevice::Keyboard, SDL_SCANCODE_ESCAPE, 0}}
    };

    setting = Action::Null;
    eventSetting = Event::Null;
}

void Input::Update() {
    InputCursor();
    InputKey();
    InputEvent();

    if (setting != Action::Null) return;
    if (eventSetting != Event::Null) return;

    for (auto& [key, value] : config) {
        value.on = 0;

        if (value.device == InputDevice::Keyboard) {
            if (keystate[value.code]) {
                value.on = 1;
            }
        }

        if (value.device == InputDevice::MouseButton) {
            if (value.code == SDL_BUTTON_LEFT) {
                if (mouse.left) {
                    value.on = 1;
                }
            }
            if (value.code == SDL_BUTTON_MIDDLE) {
                if (mouse.middle) {
                    value.on = 1;
                }
            }
            if (value.code == SDL_BUTTON_RIGHT) {
                if (mouse.right) {
                    value.on = 1;
                }
            }
            if (value.code == SDL_BUTTON_X1) {
                if (mouse.x1) {
                    value.on = 1;
                }
            }
            if (value.code == SDL_BUTTON_X2) {
                if (mouse.x2) {
                    value.on = 1;
                }
            }
        }
    }

    
}

void Input::InputCursor() {
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
    if (buttons & SDL_BUTTON(SDL_BUTTON_X1)) {
        mouse.x1 = 1;
    }
    else {
        mouse.x1 = 0;
    }
    if (buttons & SDL_BUTTON(SDL_BUTTON_X2)) {
        mouse.x2 = 1;
    }
    else {
        mouse.x2 = 0;
    }
}

void Input::InputKey() {
    keystate = SDL_GetKeyboardState(NULL);
}

void Input::InputEvent() {
    isAnyKeyPressed = 0;
    event = {};

    for (auto& [key, value] : eventConfig) {
        value.on = 0;
    }

    while (SDL_PollEvent(&e)) {
        //config
        if (setting != Action::Null) {
            if (e.type == SDL_KEYDOWN) {
                config[setting].device = InputDevice::Keyboard;
                config[setting].code = e.key.keysym.scancode;
                setting = Action::Null;
                return;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                config[setting].device = InputDevice::MouseButton;
                config[setting].code = e.button.button;
                setting = Action::Null;
                return;
            }
            if (setting != Action::Null) return;
        }

        if (eventSetting != Event::Null) {
            if (e.type == SDL_KEYDOWN) {
                eventConfig[eventSetting].device = InputDevice::Keyboard;
                eventConfig[eventSetting].code = e.key.keysym.scancode;
                eventSetting = Event::Null;
                return;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                eventConfig[eventSetting].device = InputDevice::MouseButton;
                eventConfig[eventSetting].code = e.button.button;
                eventSetting = Event::Null;
                return;
            }
            if (eventSetting != Event::Null) return;
        }

        for (auto& [key, value] : eventConfig) {
            if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
                if (value.device == InputDevice::Keyboard && value.code == e.key.keysym.scancode) {
                    value.on = 1;
                }
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (value.device == InputDevice::MouseButton && value.code == e.button.button) {
                    value.on = 1;
                }
            }
        }
        


        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            isAnyKeyPressed = 1;
            if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                event.ESCAPE = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_DELETE) {
                event.DEL = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_F1) {
                event.F1 = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_F2) {
                event.F2 = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_F3) {
                event.F3 = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_F4) {
                event.F4 = 1;
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
            if (e.key.keysym.scancode == SDL_SCANCODE_C) {
                event.C = 1;
            }
            if (e.key.keysym.scancode == SDL_SCANCODE_P) {
                event.P = 1;
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

void Input::Poll() {
    SDL_Event e;
    SDL_PollEvent(&e);
    mouse = {};
}

bool Input::GetEvent(Event event) {
    if (eventConfig[event].on) {
        eventConfig[event].on = 0;
        return true;
    }
    else {
        return false;
    }
}

void Input::SetConfig(Action action) {
    setting = action;
}

std::string Input::GetConfigName(Action action) {
    if (config[action].device == InputDevice::Keyboard) {
        return SDL_GetScancodeName((SDL_Scancode)(config[action].code));
    }
    else if (config[action].device == InputDevice::MouseButton) {
        if (config[action].code == SDL_BUTTON_LEFT) {
            return "MouseLeft";
        }
        if (config[action].code == SDL_BUTTON_MIDDLE) {
            return "MouseMiddle";
        }
        if (config[action].code == SDL_BUTTON_RIGHT) {
            return "MouseRight";
        }
        if (config[action].code == SDL_BUTTON_X1) {
            return "MouseSide1";
        }
        if (config[action].code == SDL_BUTTON_X2) {
            return "MouseSide2";
        }
    }
    return "";
}

std::string Input::GetEventConfigName(Event event) {
    if (eventConfig[event].device == InputDevice::Keyboard) {
        return SDL_GetScancodeName((SDL_Scancode)(eventConfig[event].code));
    }
    else if (eventConfig[event].device == InputDevice::MouseButton) {
        if (eventConfig[event].code == SDL_BUTTON_LEFT) {
            return "MouseLeft";
        }
        if (eventConfig[event].code == SDL_BUTTON_MIDDLE) {
            return "MouseMiddle";
        }
        if (eventConfig[event].code == SDL_BUTTON_RIGHT) {
            return "MouseRight";
        }
        if (eventConfig[event].code == SDL_BUTTON_X1) {
            return "MouseSide1";
        }
        if (eventConfig[event].code == SDL_BUTTON_X2) {
            return "MouseSide2";
        }
    }
    return "";
}

void Input::SetEventConfig(Event event) {
    eventSetting = event;
}

bool Input::IsAnyKeyPressed() {
    return isAnyKeyPressed;
}