#pragma once
#include "Button.h"
#include <vector>

class UIManager;
class Sounds;
class Textures;

class Options
{
private:
    Button SE0;
    Button SE1;
    Button SE2;
    Button SE3;
    Button SE4;
    Button SE5;
    Button SE6;
    Button SE7;
    Button SE8;
    std::vector<Button*> SE;

    Button BGM0;
    Button BGM1;
    Button BGM2;
    Button BGM3;
    Button BGM4;
    Button BGM5;
    Button BGM6;
    Button BGM7;
    Button BGM8;
    std::vector<Button*> BGM;
public:
    static UIManager* uiP;
    static Sounds* soundsP;
    static Textures* texturesP;

    Options();
    void RegisterButtons();
    void Show();
    void Hide();
    void Update();
};

