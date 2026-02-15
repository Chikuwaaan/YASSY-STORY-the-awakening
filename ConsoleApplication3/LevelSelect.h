#pragma once
#include "Timer.h"
#include "Button.h"
#include "UIManager.h"

class Textures;
class Game;

class LevelSelect
{
private:
    Timer TIMER;
    UIManager ui;

    int selected;
    int unlocked;

    LINE lineLevels;
    Button level1;
    Button level2;
    Button level3;
    Button level4;

    LINE lineTest;
    Button test1;
    Button test2;
public:
    static Textures* texturesP;
    static Game* gameP;

    LevelSelect();
    void RegisterButtons();
    void Update();
};

