#pragma once
#include "Button.h"

class UIManager;
class Textures;
class OverLay;
class Game;
class Input;

enum class Phase;

class Title
{
private:
    Button button1;
    Uint32 last;
    double timer;
    Phase phase;
    void RegisterButtons();
    void ChangePhase();
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

