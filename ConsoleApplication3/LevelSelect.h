#pragma once
#include "Timer.h"
#include "Button.h"
#include "UIManager.h"


class Textures;
class Game;
class Input;

class LevelSelect
{
private:
    Timer timer;
    Timer timer2;
    UIManager ui;

    LINE lineLevels;
    Button level1;
    Button level2;
    Button level3;
    Button level4;
    Button level5;
    Button back;
public:
    static Textures* texturesP;
    static Game* gameP;
    static Input* inputP;

    LevelSelect();
    void RegisterButtons();
    void Update();
};

