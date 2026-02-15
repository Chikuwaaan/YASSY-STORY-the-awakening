#pragma once
#include "Button.h"
#include "Options.h"
#include "UIManager.h"

class Textures;
class OverLay;
class Game;
class Input;

enum class Phase;

class Title
{
private:
    LINE titleMenu;
    Button BTNstart;
    Button BTNoptions;
    Button BTNexitgame;

    Uint32 last;
    double timer;
    Phase phase;
    void RegisterButtons();
    void ChangePhase();

    Options options;
public:
    UIManager ui;
    static Textures* texturesP;
    static OverLay* overlayP;
    static Game* gameP;
    static Input* inputP;

    Title();
    void Init();
    void Update();
};

