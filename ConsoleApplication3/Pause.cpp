#include "Pause.h"
#include "Textures.h"
#include "namespace.h"
#include "Game.h"
#include "Save.h"
#include "Input.h"

Textures* Pause::texturesP = nullptr;
Game* Pause::gameP = nullptr;
Save* Pause::saveP = nullptr;
Input* Pause::inputP = nullptr;

Pause::Pause() :
    resumeB(0, 690, 1920, 192),
    optionsB(0, 492, 1920, 192),
    saveNquitB(0, 294, 1920, 192),
    mapB(0, 96, 1920, 192)
{
    option = 0;
    on = 0;
    buttonTargetX = { -300, -200, -100, 0 };
    buttonText = {"Resume", "Options", "Save and Quit", "Return to Map"};
    description = {
        u8"ゲームを再開します",
        u8"オプション画面を開きます",
        u8"進行状況を保存してタイトル画面に戻ります",
        u8"進行状況を保存せずにステージ選択画面に戻ります"
    };

    pausingLINE = { { &resumeB, &optionsB, &saveNquitB, &mapB }, DIRECTION::V, nullptr, nullptr};
    pausingUI.AddLine(&pausingLINE);
    pausingUI.currentLine = &pausingLINE;

    Init();

    for (auto& p : pausingLINE.selectables) {
        p->texName = "toast";
        p->alpha = 0;
        p->color1 = { 255,255,255,255 };
        p->color2 = { 0,0,0,255 };
        p->textSize = 1.5;
    }
    resumeB.action = [this]() {
        on = 0;
        };
    optionsB.action = [this]() {
        option = 1;
        };
    saveNquitB.action = [this]() {
        platformer::level = 0;
        gameP->ChangeScene(Scene::Title);
        };
    mapB.action = [this]() {
        platformer::level = 0;
        platformer::CP = 0;
        platformer::coin[0] = 0;
        platformer::coin[1] = 0;
        platformer::coin[2] = 0;
        saveP->WriteProgress(savedata::slot);
        gameP->ChangeScene(Scene::LevelSelect);
        };
    options.BTNback.action = [this]() {
        option = 0;
        };

    options.RegisterButtons();
}

void Pause::Init() {
    resumeB.x = -500;
    optionsB.x = -500;
    saveNquitB.x = -500;
    mapB.x = -500;
}

void Pause::Update() {
    if (!option) {
        if (inputP->GetEvent(Event::Back)) on = 0;
    }

    if (!on) return;
    texturesP->DrawRect({0,0,0,127}, {960,540,1920,1980,1}, 0);
    if (option) {
        options.Show();
        options.Update();
        return;
    }


    int i = 0;
    for (auto& p : pausingLINE.selectables) {
        if (pausingUI.currentButton == i) {
            p->x = (int)(p->x + (buttonTargetX[i]+192 - p->x) * settings::timeScale * 8);
        }
        else {
            p->x = (int)(p->x + (buttonTargetX[i] - p->x) * settings::timeScale * 8);
        }
        p->state = State::Idle;
        i++;
    }

    pausingUI.Update();

    i = 0;
    for (auto& p : pausingLINE.selectables) {
        texturesP->DrawTexts(buttonText[i], p->color1, p->color2, { (double)p->x + 300, (double)p->y, p->textSize, p->textSize }, 0, Anchor::Left);
        if (p->state == State::OnMouse) {
            pausingUI.currentButton = i;
        }
        if (pausingUI.currentButton == i) {
            texturesP->DrawTexts(description[i], { 255,255,255,255 }, { 0,0,0,255 }, { 960,50,0.8,0.8 }, 0, Anchor::Left);
        }
        i++;
    }
}