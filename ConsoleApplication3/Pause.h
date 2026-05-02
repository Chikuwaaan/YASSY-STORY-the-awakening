#pragma once
#include "Button.h"
#include "UIManager.h"
#include "Options.h"
#include <functional>

class Textures;

class Pause
{
private:
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

    std::function<void()> back;
    Pause();
    void Init();
    void Update();
    void SetBackButton();
};

