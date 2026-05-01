#include "LevelSelect.h"
#include "Textures.h"
#include "namespace.h"
#include "Game.h"
#include "Input.h"
#include "Save.h"
#include <fstream>

Textures* LevelSelect::texturesP = nullptr;
Game* LevelSelect::gameP = nullptr;
Input* LevelSelect::inputP = nullptr;
Save* LevelSelect::saveP = nullptr;

LevelSelect::LevelSelect() :
    slot1(420, 540, 480, 960),
    slot2(960, 540, 480, 960),
    slot3(1500, 540, 480, 960),
    level1(396, 0, 768, 192),
    level2(396, 0, 768, 192),
    level3(396, 0, 768, 192),
    level4(396, 0, 768, 192),
    level5(396, 0, 768, 192),
    back(396, 0, 768, 192)
{
    phase = PhaseLevelSelect::SelectSlot;
    lineSlot = { {&slot1, &slot2, &slot3}, DIRECTION::H, nullptr, nullptr};
    lineLevels = { {&level1,&level2,&level3,&level4,&level5,&back}, DIRECTION::V, nullptr, nullptr };

    //SLOT
    slot1.texName = "slot1";
    slot1.action = [this]() {
        savedata::slot = 1;
        saveP->LoadProgress();
        if (platformer::level != 0) {
            gameP->ChangeScene(Scene::Platformer);
            return;
        }
        phase = PhaseLevelSelect::SelectLevel;
        };
    slot2.texName = "slot2";
    slot2.action = [this]() {
        savedata::slot = 2;
        saveP->LoadProgress();
        if (platformer::level != 0) {
            gameP->ChangeScene(Scene::Platformer);
            return;
        }
        phase = PhaseLevelSelect::SelectLevel;
        };
    slot3.texName = "slot3";
    slot3.action = [this]() {
        savedata::slot = 3;
        saveP->LoadProgress();
        if (platformer::level != 0) {
            gameP->ChangeScene(Scene::Platformer);
            return;
        }
        phase = PhaseLevelSelect::SelectLevel;
        };

    //LEVEL
    std::vector<std::string> levelName;
    for (int i = 1; i < 6; i++) {
        std::string path = "Levels/";
        path = path + std::to_string(i) + "/info.csv";
        std::ifstream file(path);
        std::string name;
        std::getline(file, name);

        if (savedata::completedLevel[i - 1] == 1) {
            //name = "*" + name;
        }

        levelName.push_back(name);
    }
    
    level1.text = levelName[0];
    level1.action = []() {
        platformer::level = 1;
        gameP->ChangeScene(Scene::Platformer);
        };

    level2.text = levelName[1];
    level2.action = []() {
        platformer::level = 2;
        gameP->ChangeScene(Scene::Platformer);
        };

    level3.text = levelName[2];
    level3.action = []() {
        platformer::level = 3;
        gameP->ChangeScene(Scene::Platformer);
        };

    level4.text = levelName[3];
    level4.action = []() {
        platformer::level = 4;
        gameP->ChangeScene(Scene::Platformer);
        };

    level5.text = levelName[4];
    level5.action = []() {
        platformer::level = 5;
        gameP->ChangeScene(Scene::Platformer);
        };

    back.text = "Back";
    back.action = []() {
        gameP->ChangeScene(Scene::Title);
        };

    RegisterButtons();
}

void LevelSelect::RegisterButtons() {
    UIslot.AddLine(&lineSlot);
    UIslot.currentLine = &lineSlot;
    UIlevel.AddLine(&lineLevels);
    UIlevel.currentLine = &lineLevels;
}

void LevelSelect::Update() {
    OBJRECT bg = { 0 , settings::baseH / 2.0, settings::baseW * 2.0, settings::baseH * 1.0 };
    double time = timer.GetTime();
    bg.x = time * 100;
    if (bg.x >= 1920) {
        timer.Reset();
    }
    texturesP->DrawImage("LevelSelect", bg, 0, {});

    if (phase == PhaseLevelSelect::SelectSlot) {
        slot1.state = State::Idle;
        slot2.state = State::Idle;
        slot3.state = State::Idle;
        UIslot.Update();

        SDL_Color color1 = { 255,255,255,255 };
        SDL_Color color2 = { 0,73,220,255 };
        texturesP->DrawImage("zero_percent", { 420,540,480,960 }, 0, {});
        texturesP->DrawTexts(u8"ヤッシィ１号", color1, color2, { 420,800,1.5,1.5 }, 0, Anchor::Center);
        texturesP->DrawImage("zero_percent", { 960,540,480,960 }, 0, {});
        texturesP->DrawTexts(u8"ヤッシィ２号", color1, color2, { 960,800,1.5,1.5 }, 0, Anchor::Center);
        texturesP->DrawImage("zero_percent", { 1500,540,480,960 }, 0, {});
        texturesP->DrawTexts(u8"ヤッシィ３号", color1, color2, { 1500,800,1.5,1.5 }, 0, Anchor::Center);
    }

    if (phase == PhaseLevelSelect::SelectLevel) {
        std::string thumbnail = "thumbnail";
        thumbnail = thumbnail + std::to_string(UIlevel.currentButton + 1);
        texturesP->DrawImage(thumbnail, { 1600,540,512,512 }, 0, {});
        texturesP->DrawImage("whitestar", { 1100,540,400,400 }, 0, {});

        double time2 = timer2.GetTime();
        for (int i = 0; i < 5; i++) {
            double size;
            if (UIlevel.currentButton == i) {
                size = 100 + sin(time2 * 4) * 20;
            }
            else {
                size = 100;
            }

            texturesP->DrawImage("Bhead",
                {
                1100 + cos(utilities::DegreetoRadian(i * -72 + 90)) * 200,
                540 + sin(utilities::DegreetoRadian(i * -72 + 90)) * 200,
                size,
                size },
                0,
                {});
            if (UIlevel.currentButton == i) {
                texturesP->DrawImage("Bface",
                    {
                    1100 + cos(utilities::DegreetoRadian(i * -72 + 90)) * 200,
                    540 + sin(utilities::DegreetoRadian(i * -72 + 90)) * 200,
                    size,
                    size },
                    0,
                    {});
            }
        }

        for (int i = 0; i < 3; i++) {
            texturesP->DrawSprite("coinmanager", { 1600.0 - 96 + 96 * i,236,96,96 }, { 16 * savedata::coin[UIlevel.currentButton][i],0,16,16 }, 0);
        }

        int i = 0;
        for (auto& p : lineLevels.selectables) {
            p->state = State::Idle;
            double targetY = i * -204 + UIlevel.currentButton * 204 + 540;
            p->y = (int)(p->y + (targetY - p->y) * settings::timeScale * 8);

            if (savedata::completedLevel[i] == 1) {
                texturesP->DrawImage("whitestar", { 820,p->y + 75.0,50,50 }, 0, {});
            }
            for (int j = 0; j < 3; j++) {
                OBJRECT dst = { 820,p->y + 25.0 - j * 50,50,50 };
                SDL_Rect src = { savedata::coin[i][j]*16, 0, 16,16 };
                texturesP->DrawSprite("coinmanager", dst, src, 0);
            }

            i++;
        }

        EVENT event = inputP->event;
        if (event.MouseWheel == 1) {
            UIlevel.ChangeCurrentButton(-1);
        }
        else if (event.MouseWheel == -1) {
            UIlevel.ChangeCurrentButton(1);
        }

        UIlevel.Update();
    }
    
}