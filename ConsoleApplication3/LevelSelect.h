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

    int unlocked;
public:
    static Textures* texturesP;
    static Game* gameP;

    LevelSelect();
    void RegisterButtons();
    void Update();
};

