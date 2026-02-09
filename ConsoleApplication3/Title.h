#pragma once
#include "Button.h"
#include "Options.h"

class UIManager;
class Textures;
class OverLay;
class Game;
class Input;

enum class Phase;

class Title
{
private:
    Button BTNback;
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
    static UIManager* uiP;
    static Textures* texturesP;
    static OverLay* overlayP;
    static Game* gameP;
    static Input* inputP;

    Title();
    void Init();
    void Update();
};

