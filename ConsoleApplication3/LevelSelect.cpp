#include "LevelSelect.h"
#include "Textures.h"
#include "namespace.h"
#include "Game.h"
#include "Input.h"
#include <fstream>

Textures* LevelSelect::texturesP = nullptr;
Game* LevelSelect::gameP = nullptr;
Input* LevelSelect::inputP = nullptr;

LevelSelect::LevelSelect() :
    level1(396, 0, 768, 192),
    level2(396, 0, 768, 192),
    level3(396, 0, 768, 192),
    level4(396, 0, 768, 192),
    back(396, 0, 768, 192)
{
    lineLevels = { {&level1,&level2,&level3,&level4,&back}, DIRECTION::V, nullptr, nullptr };

    std::vector<std::string> levelName;
    for (int i = 1; i < 5; i++) {
        std::string path = "Levels/";
        path = path + std::to_string(i) + "/info.csv";
        std::ifstream file(path);
        std::string name;
        std::getline(file, name);
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

    back.text = "Back";
    back.action = []() {
        gameP->ChangeScene(Scene::Title);
        };

    RegisterButtons();
}

void LevelSelect::RegisterButtons() {
    ui.AddLine(&lineLevels);
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

    std::string thumbnail = "thumbnail";
    thumbnail = thumbnail + std::to_string(ui.currentButton+1);
    texturesP->DrawImage(thumbnail, {1500,540,512,512}, 0, {});

    int i = 0;
    for (auto& p : lineLevels.selectables) {
        p->state = State::Idle;
        double targetY = i * -204 + ui.currentButton * 204 + 540;
        p->y = p->y + (targetY - p->y) * settings::timeScale * 8;
        i++;
    }

    EVENT event = inputP->event;
    if (event.MouseWheel == 1) {
        ui.ChangeCurrentButton(-1);
    }
    else if (event.MouseWheel == -1) {
        ui.ChangeCurrentButton(1);
    }

    ui.Update();
    
    //camera.x = camera.x + (camera.targetX - camera.x) * settings::timeScale * 8;
}