#pragma once

#include <SDL.h>
#include <unordered_map>
#include <string>

struct MOUSE {
    int x;
    int y;
    bool left;
    bool middle;
    bool right;
    bool x1;
    bool x2;
};

struct EVENT {
    bool ESCAPE;
    bool DEL;
    bool F1;
    bool F2;
    bool F3;
    bool F4;
    bool F12;
    bool RETURN;
    bool SPACE;
    bool Q;
    bool E;
    bool C;
    bool P;
    bool Up;
    bool Down;
    bool Left;
    bool Right;
    int MouseWheel;
    bool MouseLeft;
    bool MouseMiddle;
    bool MouseRight;
    bool MouseX1;
    bool MouseX2;
};

enum class InputDevice {
    Keyboard,
    MouseButton
};

struct InputType {
    InputDevice device;
    int code;
    bool on;
};

enum class Action {
    Null,
    HoldUp,
    HoldDown,
    HoldLeft,
    HoldRight,
    HoldJump,
    HoldRun
};

class Input
{
private:
    bool isAnyKeyPressed;
    SDL_Event e;
public:
    std::unordered_map<Action, InputType> config;
    std::unordered_map<Action, InputType> eventConfig;

    Action setting;
    const Uint8* keystate;
    EVENT event;
    MOUSE mouse;

    Input();
    void Update();
    void InputCursor();
    void InputKey();
    void InputEvent();

    void SetConfig(Action action);
    std::string GetConfigName(Action action);
   
    bool IsAnyKeyPressed();
};

