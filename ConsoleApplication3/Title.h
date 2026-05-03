#pragma once
#include "Button.h"
#include "Options.h"
#include "UIManager.h"

class Textures;
class OverLay;
class Game;
class Input;
class Sounds;

enum class Phase;

class Title
{
private:
    LINE titleMenu;
    Button BTNstart;
    Button BTNoptions;
    Button BTNcredits;
    Button BTNexitgame;
    LINE face;
    Button BTNface;
    Button BTNback;

    Uint32 last;
    double timer;
    Phase phase;
    void RegisterButtons();
    void ChangePhase();

    Options options;
public:
    UIManager ui;
    UIManager uiCredits;
    static Textures* texturesP;
    static OverLay* overlayP;
    static Game* gameP;
    static Input* inputP;
    static Sounds* soundsP;

    Title();
    void Init();
    void Update();
};

