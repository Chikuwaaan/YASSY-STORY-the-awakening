#include "Complete.h"
#include "namespace.h"
#include "Textures.h"

Textures* Complete::texturesP = nullptr;

Complete::Complete() {
    clearTime = 0;
}

void Complete::Update() {
    OBJRECT bg = { 0 , settings::baseH / 2.0, settings::baseW * 2.0, settings::baseH * 1.0 };
    double time = timer.GetTime();
    bg.x = time * 100;
    if (bg.x >= 1920) {
        timer.Reset();
    }
    texturesP->DrawImage("LevelSelect", bg, 0, {});

    texturesP->DrawTexts(std::to_string(clearTime), {255,255,255,255}, { 0,73,220,255 }, { 960, 500, 2, 2 }, 0, Anchor::Center);
}

void Complete::SetClearTime(double time) {

}