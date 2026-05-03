#pragma once
#include "Button.h"
#include "UIManager.h"
#include "Options.h"
#include <functional>

class Textures;
class Game;
class Save;
class Input;

class Pause
{
private:
    bool option;
    Options options;

    UIManager pausingUI;
    LINE pausingLINE;
    Button resumeB;
    Button optionsB;
    Button saveNquitB;
    Button mapB;
    std::vector<double> buttonTargetX;
    std::vector<std::string> buttonText;
    std::vector<std::u8string> description;
public:
    static Textures* texturesP;
    static Game* gameP;
    static Save* saveP;
    static Input* inputP;

    bool on;

    Pause();
    void Init();
    void Update();
};

