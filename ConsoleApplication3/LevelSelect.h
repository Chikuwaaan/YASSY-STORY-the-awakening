#pragma once
#include "Timer.h"
#include "Button.h"
#include "UIManager.h"

class Textures;
class Game;

class LevelSelect
{
private:
    Timer timerBG;
    UIManager ui;

    LINE lineLevels;
    Button level1;
    Button level2;
    Button level3;
    Button level4;
public:
    static Textures* texturesP;
    static Game* gameP;

    LevelSelect();
    void RegisterButtons();
    void Update();
};

