#include "LevelSelect.h"
#include "Textures.h"
#include "namespace.h"
#include "Game.h"
#include "Input.h"
#include "Save.h"
#include "Rand.h"
#include "Sounds.h"
#include <fstream>
#include <filesystem>

Textures* LevelSelect::texturesP = nullptr;
Game* LevelSelect::gameP = nullptr;
Input* LevelSelect::inputP = nullptr;
Save* LevelSelect::saveP = nullptr;
Sounds* LevelSelect::soundsP = nullptr;

LevelSelect::LevelSelect() :
    slot1(420, 440, 480, 720),
    slot2(960, 440, 480, 720),
    slot3(1500, 440, 480, 720),
    level1(396, 0, 768, 192),
    level2(396, 0, 768, 192),
    level3(396, 0, 768, 192),
    level4(396, 0, 768, 192),
    level5(396, 0, 768, 192),
    level6(396, 0, 768, 192),
    level7(396, 0, 768, 192),
    back(396, 0, 768, 192)
{
    assy.SetX(1880);
    assy.SetY(950);
    assy.FlipX(1);

    soundsP->PlayMusic("f");
    saveP->LoadProgress(savedata::slot);
    phase = PhaseLevelSelect::SelectSlot;
    Init();
    percent[0] = 0;
    percent[1] = 0;
    percent[2] = 0;
    isSavedataExisting[0] = 0;
    isSavedataExisting[1] = 0;
    isSavedataExisting[2] = 0;

    //SLOT
    slot1.texName = "slot1";
    slot1.action = [this]() {
        savedata::slot = 1;
        saveP->LoadProgress(1);
        if (platformer::level != 0) {
            gameP->ChangeScene(Scene::Platformer);
            return;
        }
        phase = PhaseLevelSelect::SelectLevel;
        Init();
        };
    slot2.texName = "slot2";
    slot2.action = [this]() {
        savedata::slot = 2;
        saveP->LoadProgress(2);
        if (platformer::level != 0) {
            gameP->ChangeScene(Scene::Platformer);
            return;
        }
        phase = PhaseLevelSelect::SelectLevel;
        Init();
        };
    slot3.texName = "slot3";
    slot3.action = [this]() {
        savedata::slot = 3;
        saveP->LoadProgress(3);
        if (platformer::level != 0) {
            gameP->ChangeScene(Scene::Platformer);
            return;
        }
        phase = PhaseLevelSelect::SelectLevel;
        Init();
        };

    //LEVEL
    std::vector<std::string> levelName;
    for (int i = 1; i <= 7; i++) {
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

    level5.text = levelName[4];
    level5.action = []() {
        platformer::level = 5;
        gameP->ChangeScene(Scene::Platformer);
        };

    level6.text = levelName[5];
    level6.action = []() {
        platformer::level = 6;
        gameP->ChangeScene(Scene::Platformer);
        };

    level7.text = levelName[6];
    level7.action = []() {
        platformer::level = 7;
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
        SDL_Color color3 = { 255,37,87,255 };
        std::string textPercent1 = std::to_string(percent[0]) + "%";
        std::string textPercent2 = std::to_string(percent[1]) + "%";
        std::string textPercent3 = std::to_string(percent[2]) + "%";
        std::u8string textName1 = isSavedataExisting[0] ? u8"ヤッシィ１号" : u8"NEW☆GAME";
        std::u8string textName2 = isSavedataExisting[1] ? u8"ヤッシィ２号" : u8"NEW☆GAME";
        std::u8string textName3 = isSavedataExisting[2] ? u8"ヤッシィ３号" : u8"NEW☆GAME";
        std::u8string zenkuri = u8"全クリ";

        int angle = random.random(0,359);
        texturesP->DrawImage("assy", { 960 - 750,1000,100,100 }, 0, { 1,angle * 1.0,50,50});
        angle = random.random(0, 359);
        texturesP->DrawImage("assy", { 960 + 750,1000,100,100 }, 0, { 1,angle * 1.0,50,50 });
        texturesP->DrawTexts("*Select Your Saved Game*", color1, color2, {960,1000,2,2}, 0, Anchor::Center);
        
        texturesP->DrawImage("zero_percent", { 420,440,480,720 }, 0, {});
        texturesP->DrawTexts(textName1, color1, color2, { 420,700,1.5,1.5 }, 0, Anchor::Center);
        texturesP->DrawTexts(textPercent1, color1, color2, {420,200,1.5,1.5}, 0, Anchor::Center);
        if (percent[0] == 1008) texturesP->DrawTexts(zenkuri, color1, color3, {420,450,2,2}, 0, Anchor::Center);

        texturesP->DrawImage("zero_percent", { 960,440,480,720 }, 0, {});
        texturesP->DrawTexts(textName2, color1, color2, { 960,700,1.5,1.5 }, 0, Anchor::Center);
        texturesP->DrawTexts(textPercent2, color1, color2, { 960,200,1.5,1.5 }, 0, Anchor::Center);
        if (percent[1] == 1008) texturesP->DrawTexts(zenkuri, color1, color3, { 960,450,2,2 }, 0, Anchor::Center);

        texturesP->DrawImage("zero_percent", { 1500,440,480,720 }, 0, {});
        texturesP->DrawTexts(textName3, color1, color2, { 1500,700,1.5,1.5 }, 0, Anchor::Center);
        texturesP->DrawTexts(textPercent3, color1, color2, { 1500,200,1.5,1.5 }, 0, Anchor::Center);
        if (percent[2] == 1008) texturesP->DrawTexts(zenkuri, color1, color3, { 1500,450,2,2 }, 0, Anchor::Center);
    }

    if (phase == PhaseLevelSelect::SelectLevel) {
        assy.DrawA();
        assy.moveBody += 0.1;

        SDL_Color color1 = { 255,255,255,255 };
        SDL_Color color2 = { 0,73,220,255 };
        SDL_Color color3 = { 255,37,87,255 };
        std::string thumbnail = "thumbnail";
        thumbnail = thumbnail + std::to_string(availableLevels[UIlevel.currentButton] + 1);
        texturesP->DrawTexts(u8"やっしー　号", color1, color2, {1500,950,2,2}, 0, Anchor::Center);
        texturesP->DrawTexts(std::to_string(savedata::slot), color1, color2, {1640,950,3,3}, 0, Anchor::Center);
        texturesP->DrawImage(thumbnail, { 1600,540,512,512 }, 0, {});
        texturesP->DrawImage("whitestar", { 1100,540,400,400 }, 0, {});
        if (savedata::completedLevel[4] == 2) texturesP->DrawTexts(u8"GAME CLEAR!", color1, color3, { 1500,850,1,1 }, 0, Anchor::Center);

        double time2 = timer2.GetTime();
        for (auto& i : availableLevels) {
            if (0 <= i && i < 5) {
                double size;
                if (availableLevels[UIlevel.currentButton] == i) {
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
                if (availableLevels[UIlevel.currentButton] == i) {
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
            if ((i == 5 || i== 6) && availableLevels[UIlevel.currentButton] == i) {
                double size;
                if (availableLevels[UIlevel.currentButton] == i) {
                    size = 400 + sin(time2 * 4) * 50;
                }
                else {
                    size = 400;
                }
                texturesP->DrawImage("Bface", { 1100,540,size,size }, 0, {});
            }
        }

        //サムネイルの下
        if (availableLevels[UIlevel.currentButton] != 1007) {
            for (int i = 0; i < 3; i++) {
                texturesP->DrawSprite("coinmanager", { 1600.0 - 96 + 96 * i,236,96,96 }, { 16 * savedata::coin[UIlevel.currentButton][i],0,16,16 }, 0);
            }
            std::string text = "Best Time:";
            text = text + std::format("{:.3f}", savedata::time[UIlevel.currentButton]);
            texturesP->DrawTexts(text, color1, color2, { 1600,100,1,1 }, 0, Anchor::Center);
        }

        int i = 0;
        for (auto& p : lineLevels.selectables) {
            p->state = State::Idle;
            double targetY = i * -204 + UIlevel.currentButton * 204 + 540;
            p->y = (int)(p->y + (targetY - p->y) * settings::timeScale * 8);

            if (availableLevels[i] == 1007) break;

            if (savedata::completedLevel[i] == 2) {
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

void LevelSelect::Init() {
    lineSlot = { {&slot1, &slot2, &slot3}, DIRECTION::H, nullptr, nullptr };
    lineLevels = { {}, DIRECTION::V, nullptr, nullptr };

    for (int i = 0; i < 4; i++) {
        if (savedata::completedLevel[i] == 2) {
            if (savedata::completedLevel[i + 1] == 0) {
                savedata::completedLevel[i + 1] = 1;
            }
        }
    }

    bool six = 1;
    for (int i = 0; i < 5; i++) {
        if (savedata::completedLevel[i] != 2) six = 0;
        if (savedata::coin[i][0] != 1 || savedata::coin[i][1] != 1 || savedata::coin[i][2] != 1) six = 0;
    }
    if (six && savedata::completedLevel[5] == 0) savedata::completedLevel[5] = 1;

    if (savedata::completedLevel[5] == 2) {
        if (savedata::completedLevel[6] == 0) {
            savedata::completedLevel[6] = 1;
        }
    }

    availableLevels = {};
    std::vector<Button*> levels = { &level1,&level2,&level3,&level4,&level5,&level6,&level7 };
    for (int i = 0; i < 7; i++) {
        if (savedata::completedLevel[i] != 0) {
            availableLevels.push_back(i);
            lineLevels.selectables.push_back(levels[i]);
        }
    }
    availableLevels.push_back(1007);
    lineLevels.selectables.push_back(&back);
}

void LevelSelect::GetPercent() {
    namespace fs = std::filesystem;
    for (int i = 0; i < 3; i++) {
        std::string path = "Save/";
        path = path + std::to_string(i+1) + "/progress.bin";
        if (fs::exists(path)) {
            isSavedataExisting[i] = 1;
        }
    }
    

    for (int i = 0; i < 3; i++) {
        saveP->LoadProgress(i+1);

        int j = 0;
        double per = 0.0;
        for (auto& p : savedata::completedLevel) {
            if (p == 2) {
                if (j < 5) {
                    per += 0.1;
                }
                else {
                    per += 4.54 / 4;
                }
            }
            j++;
        }
        j = 0;
        for (auto& p : savedata::coin) {
            for (auto& q : p) {
                if (q == 1) {
                    if (j < 5) {
                        per += 0.1 / 3;
                    }
                    else {
                        per += 4.54 / 4;
                    }
                }
            }
            j++;
        }

        percent[i] = (int)round(per * 100);
    }
    platformer::level = 0;
    platformer::CP = 0;
    platformer::coin[0] = 0;
    platformer::coin[1] = 0;
    platformer::coin[2] = 0;
}