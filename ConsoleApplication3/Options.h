#pragma once
#include "Button.h"
#include <vector>
#include "UIManager.h"

class Sounds;
class Textures;
class Input;

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

    LINE lineBGM;
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

    LINE config1;
    LINE config2;
    Button Up;
    Button Down;
    Button Left;
    Button Right;
    Button Jump;
    Button Dash;
    Button Confirm;
    Button Back;
    std::vector<Button*> CONFIGS1;
    std::vector<Button*> CONFIGS2;

    LINE sita;
    Button Invert;
    Button Blur;
    Button Eye;

    LINE sita2;
    Button Une;
    Button Tomato;

    LINE back; 
public:
    static Input* inputP;

    LINE lineSE;

    Button BTNback;

    UIManager ui;
    static Sounds* soundsP;
    static Textures* texturesP;

    Options();
    void RegisterButtons();
    void Show();
    void Hide();
    void Update();
};

