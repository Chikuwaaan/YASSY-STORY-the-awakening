#include "LevelSelect.h"
#include "Textures.h"
#include "namespace.h"
#include "Game.h"

Textures* LevelSelect::texturesP = nullptr;
Game* LevelSelect::gameP = nullptr;

LevelSelect::LevelSelect() :
    level1(0, 500, 96, 96),
    level2(0, 500, 96, 96),
    level3(0, 500, 96, 96),
    level4(0, 500, 96, 96)
{
    lineLevels = { {&level1,&level2,&level3,&level4}, DIRECTION::H, nullptr, nullptr };
    

    RegisterButtons();
}

void LevelSelect::RegisterButtons() {
    ui.AddLine(&lineLevels);

    int i = 0;
    for (auto& p : lineLevels.selectables) {
        p->x = i * 300 + 300;
        i++;
    }
    
    ui.currentLine = &lineLevels;
}

void LevelSelect::Update() {
    OBJRECT bg = { 0 , settings::baseH / 2.0, settings::baseW * 2.0, settings::baseH * 1.0 };
    double timer = timerBG.GetTime();
    bg.x = timer * 100;
    if (bg.x >= 1920) {
        timerBG.Reset();
    }
    texturesP->DrawImage("LevelSelect", bg, 0, {});

    int i = 0;
    for (auto& p : lineLevels.selectables) {
        p->state = State::Idle;

        i++;
    }

    ui.Update();
}