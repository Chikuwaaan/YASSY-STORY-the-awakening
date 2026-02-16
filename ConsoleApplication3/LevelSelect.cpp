#include "LevelSelect.h"
#include "Textures.h"
#include "namespace.h"
#include "Game.h"

Textures* LevelSelect::texturesP = nullptr;
Game* LevelSelect::gameP = nullptr;

LevelSelect::LevelSelect() :
    level1(0, 500, 96, 96),
    level2(0, 500, 96, 96),
    level3(0, 500, 192, 96),
    level4(0, 500, 192, 192),
    test1(500, 200, 96, 96),
    test2(1000,200,96,96)
{
    lineLevels = { {&level1,&level2,&level3,&level4}, DIRECTION::H, nullptr, &lineTest };
    lineTest = { {&test1,&test2}, DIRECTION::H, &lineLevels, nullptr };
    

    selected = 2;
    unlocked = 4;
    RegisterButtons();
}

void LevelSelect::RegisterButtons() {
    ui.AddLine(&lineLevels);
    ui.AddLine(&lineTest);

    int i = 0;
    for (auto& p : lineLevels.selectables) {
        p->x = i * 300 + 300;
        i++;
    }
    
    ui.currentLine = &lineLevels;
}

void LevelSelect::Update() {
    OBJRECT bg = { 0 , settings::baseH / 2.0, settings::baseW * 2.0, settings::baseH * 1.0 };
    double timer = TIMER.GetTime();
    bg.x = timer * 100;
    if (bg.x >= 1920) {
        TIMER.Reset();
    }
    texturesP->DrawImage("LevelSelect", bg, 0, {});

    int i = 0;
    for (auto& p : lineLevels.selectables) {
        p->state = State::Idle;

        i++;
    }

    ui.Update();
}