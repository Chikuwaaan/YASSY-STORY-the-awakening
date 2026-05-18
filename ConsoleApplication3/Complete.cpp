#include "Complete.h"
#include "namespace.h"
#include "Textures.h"
#include <format>

Textures* Complete::texturesP = nullptr;

Complete::Complete() : 
    next(1824,96,192,192)
{
    clearTime = 0;
    bestTime = 0;
    deaths = 0;
    y = { 1300, 1300, 1300, 1300};
    targetY = { 940,540,240,120 };
    levelName = u8"";
    finish = 0;

    next.icon = Icons::Right;
    next.action = [this]() {
        finish = 1;
        };

    line = {
        {&next},
        DIRECTION::H
    };
    ui.AddLine(&line);
    ui.currentLine = &line;
}

void Complete::Update() {
    OBJRECT bg = { 0 , settings::baseH / 2.0, settings::baseW * 2.0, settings::baseH * 1.0 };
    double time = bgTimer.GetTime();
    bg.x = time * 100;
    if (bg.x >= 1920) {
        bgTimer.Reset();
    }
    texturesP->DrawImage("LevelSelect", bg, 0, {});

    textTimer.Update();
    for (int i = 0; i < 4; i++) {
        if (textTimer.GetTime() * 200/240 > i) {
            y[i] = (y[i] + (targetY[i] - y[i]) * settings::timeScale * 16);
        }
    }

    std::u8string newRecord;
    if (clearTime < bestTime) {
        newRecord = u8"NEW☆RECORD";
    }
    else {
        newRecord = u8"";
    }

    std::u8string noDeath;
    if (deaths == 0) {
        noDeath = u8"NO☆DEATH";
    }

    std::u8string text1 = u8"LEVEL☆COMPLETE";
    std::string text2 = "Time:";
    text2 = text2 + std::format("{:.3f}", clearTime);
    std::string text3 = "Best Time:";
    text3 = text3 + std::format("{:.3f}", bestTime);
    std::string text4 = "Deaths:";
    text4 = text4 + std::to_string(deaths);
    texturesP->DrawTexts(text1, { 100,200,255,255 }, { 0,73,220,255 }, { 960, y[0], 3, 3 }, 0, Anchor::Center);
    texturesP->DrawTexts(levelName, { 255,255,255,255 }, { 0,0,128,255 }, { 960, y[0]-100, 2, 2 }, 0, Anchor::Center);
    texturesP->DrawTexts(text2, { 255,255,255,255 }, { 0,73,220,255 }, { 960, y[1], 2, 2 }, 0, Anchor::Center);
    texturesP->DrawTexts(text3, { 255,255,255,255 }, { 0,73,220,255 }, { 960, y[1]-75, 1, 1 }, 0, Anchor::Center);
    texturesP->DrawTexts(newRecord, { 255,255,255,255 }, { 255,37,87,255 }, { 960, y[1]+100, 1.5, 1.5 }, 0, Anchor::Center);
    texturesP->DrawTexts(text4, { 255,255,255,255 }, { 0,73,220,255 }, { 960, y[2], 2, 2 }, 0, Anchor::Center);
    texturesP->DrawTexts(noDeath, { 255,255,255,255 }, { 255,37,87,255 }, { 960, y[2]+100, 1.5, 1.5 }, 0, Anchor::Center);
    texturesP->DrawImage("yassy_art1", { 120,y[3],320,240}, 0, {0,0,0,0,1});

    next.state = State::Idle;
    ui.Update();
}

void Complete::SetClearTime(double time) {
    clearTime = time;
}

void Complete::SetBestTime(double time) {
    bestTime = time;
}

void Complete::SetDeaths(int n) {
    deaths = n;
}