#include "LevelSelect.h"
#include "Textures.h"
#include "namespace.h"
#include "Game.h"

Textures* LevelSelect::texturesP = nullptr;
Game* LevelSelect::gameP = nullptr;

LevelSelect::LevelSelect() 
{
    unlocked = 4;
    RegisterButtons();
}

void LevelSelect::RegisterButtons() {
    int i = 0;
    for (i; i < 4; i++) {
        std::unique_ptr<Button> a;
        a = std::make_unique<Button>(100 * i, 100, 100, 100);
        ui.AddButton(a.get());
        //a->visible = 1;
    }
}

void LevelSelect::Update() {
    OBJRECT bg = { 0 , settings::baseH / 2.0, settings::baseW * 2.0, settings::baseH * 1.0 };
    double timer = TIMER.GetTime();
    bg.x = timer * 100;
    if (bg.x >= 1920) {
        TIMER.Reset();
    }
    texturesP->DrawImage("LevelSelect", bg, 0, {});

    ui.Update();
}