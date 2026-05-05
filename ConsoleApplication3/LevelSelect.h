#pragma once
#include "Timer.h"
#include "Button.h"
#include "UIManager.h"
#include "Rand.h"
#include "Player.h"


class Textures;
class Game;
class Input;
class Save;

enum class PhaseLevelSelect {
    SelectSlot,
    SelectLevel
};

class LevelSelect
{
private:
    Timer timer;
    Timer timer2;
    Rand random;

    UIManager UIslot;
    LINE lineSlot;
    Button slot1;
    Button slot2;
    Button slot3;

    UIManager UIlevel;
    LINE lineLevels;
    Button level1;
    Button level2;
    Button level3;
    Button level4;
    Button level5;
    Button back;

    int percent[3];
    bool isSavedataExisting[3];
    std::vector<int> availableLevels;

    Player assy;
public:
    static Textures* texturesP;
    static Game* gameP;
    static Input* inputP;
    static Save* saveP;

    PhaseLevelSelect phase;

    LevelSelect();
    void RegisterButtons();
    void Update();
    void Init();
    void GetPercent();
};

