#include "Platformer.h"
#include "Textures.h"
#include "Camera.h"
#include "namespace.h"
#include "GameObject.h"
#include "Lift.h"
#include "Zako.h"
#include "Input.h"
#include "CheckPoint.h"
#include "BackGround.h"
#include "SDL_mixer.h"
#include "Sounds.h"
#include "LiftFall.h"
#include "Toast.h"
#include "ZakoJump.h"
#include "JumpPad.h"
#include "Goal.h"
#include "Deco.h"
#include "Warp.h"
#include "Hossy.h"
#include "Hosi.h"
#include "Coin.h"
#include "Spawner.h"
#include "Water.h"
#include "Particle.h"
#include "Fishy.h"
#include "Coco.h"
#include "Fan.h"
#include "Tomato.h"

#include "Save.h"
#include "Game.h"

#include <iostream>
#include <fstream>
#include <variant>

Textures* Platformer::texturesP = nullptr;
Camera* Platformer::cameraP = nullptr;
Input* Platformer::inputP = nullptr;
Sounds* Platformer::soundsP = nullptr;
Save* Platformer::saveP = nullptr;
Game* Platformer::gameP = nullptr;

Platformer::Platformer() {
    player.levelP = &level;
    Level::playerP = &player;
    GameObject::levelP = &level;
    GameObject::playerP = &player;
    Coin::managerP = &coinManager;
    editorMode = 0;
    pausing = 0;
    completed = 0;
    autoScroll = 0;
}

void Platformer::LoadLevelInfo() {
    std::string path = "Levels/";
    path = path + std::to_string(platformer::level) + "/info.csv";
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "[DEBUG]failed to open file: " << path << std::endl;
    }

    std::string name;
    std::getline(file, name);
    info.name = reinterpret_cast<const char8_t*>(name.c_str());
    std::getline(file, info.BGM);
}

GameObject* Platformer::AddObject(std::string objClass, std::vector<std::variant<double, std::string>> args) {
    std::unique_ptr<GameObject> p = nullptr;

    if (objClass == "Zako") {
        p = std::make_unique<Zako>(std::get<double>(args[0]), std::get<double>(args[1]));
    }
    if (objClass == "Lift") {
        p = std::make_unique<Lift>(
            std::get<double>(args[0]),
            std::get<double>(args[1]),
            std::get<double>(args[2]),
            std::get<double>(args[3]),
            std::get<double>(args[4]),
            std::get<double>(args[5]),
            std::get<double>(args[6]),
            std::get<double>(args[7])
        );
    }
    if (objClass == "LiftFall") {
        p = std::make_unique<LiftFall>(
            std::get<double>(args[0]),
            std::get<double>(args[1]),
            std::get<double>(args[2])
        );
    }
    if (objClass == "CheckPoint") {
        p = std::make_unique<CheckPoint>(
            std::get<double>(args[0]),
            std::get<double>(args[1]),
            std::get<double>(args[2])
        );
    }
    if (objClass == "BackGround") {
        p = std::make_unique<BackGround>(
            std::get<double>(args[0]),
            std::get<double>(args[1]),
            std::get<double>(args[2]),
            std::get<double>(args[3]),
            std::get<double>(args[4]),
            std::get<double>(args[5]),
            std::get<double>(args[6]),
            std::get<std::string>(args[7])
        );
    }
    if (objClass == "ZakoJump") {
        p = std::make_unique<ZakoJump>(
            std::get<double>(args[0]),
            std::get<double>(args[1])
        );
    }
    if (objClass == "JumpPad") {
        p = std::make_unique<JumpPad>(
            std::get<double>(args[0]),
            std::get<double>(args[1])
        );
    }
    if (objClass == "Goal") {
        p = std::make_unique<Goal>(
            std::get<double>(args[0]),
            std::get<double>(args[1]),
            std::get<double>(args[2]),
            std::get<double>(args[3])
        );
    }
    if (objClass == "Deco") {
        p = std::make_unique<Deco>(
            std::get<double>(args[0]),
            std::get<double>(args[1]),
            std::get<double>(args[2]),
            std::get<double>(args[3]),
            std::get<double>(args[4]),
            std::get<std::string>(args[5])
        );
    }
    if (objClass == "Warp") {
        std::unique_ptr<Warp>
            p0 = std::make_unique<Warp>(
                std::get<double>(args[0]),
                std::get<double>(args[1]),
                0
            );

        std::unique_ptr<Warp>
            p1 = std::make_unique<Warp>(
                std::get<double>(args[2]),
                std::get<double>(args[3]),
                1
            );
        
        p0->pair = p1.get();
        p1->pair = p0.get();
        pendingObjects.push_back(std::move(p0));
        pendingObjects.push_back(std::move(p1));
    }
    if (objClass == "Hossy") {
        p = std::make_unique<Hossy>(
            std::get<double>(args[0]),
            std::get<double>(args[1])
        );
    }
    if (objClass == "Hosi") {
        p = std::make_unique<Hosi>(
            std::get<double>(args[0]),
            std::get<double>(args[1]),
            std::get<double>(args[2])
        );
    }
    if (objClass == "Coin") {
        p = std::make_unique<Coin>(
            std::get<double>(args[0]),
            std::get<double>(args[1]),
            std::get<double>(args[2])
        );
    }
    if (objClass == "SpawnerR") {
        p = std::make_unique<Spawner>("assy", args);
    }
    if (objClass == "SpawnerL") {
        p = std::make_unique<Spawner>("assy2", args);
    }
    if (objClass == "Water") {
        p = std::make_unique<Water>(
            std::get<double>(args[0]),
            std::get<double>(args[1]),
            std::get<double>(args[2]),
            std::get<double>(args[3])
        );
    }
    if (objClass == "Particle") {
        p = std::make_unique<Particle>(
            std::get<double>(args[0]),
            std::get<double>(args[1]),
            std::get<std::string>(args[2])
        );
    }
    if (objClass == "Fishy") {
        p = std::make_unique<Fishy>(
            std::get<double>(args[0]),
            std::get<double>(args[1]),
            std::get<double>(args[2])
        );
    }
    if (objClass == "Coco") {
        pendingObjects.push_back(std::make_unique<Deco>(
            std::get<double>(args[0]),
            std::get<double>(args[1])+240-48,
            480,
            480,
            -1,
            "palm"
        ));
        int n = (int)std::get<double>(args[2]);
        if (n > 0) {
            pendingObjects.push_back(std::make_unique<Coco>(
                std::get<double>(args[0]) - 30,
                std::get<double>(args[1]) + 288
            ));
            if (n > 1) {
                pendingObjects.push_back(std::make_unique<Coco>(
                    std::get<double>(args[0]) + 30,
                    std::get<double>(args[1]) + 288
                ));
            }
        }
    }
    if (objClass == "Fan") {
        p = std::make_unique<Fan>(
            std::get<double>(args[0]),
            std::get<double>(args[1]),
            std::get<double>(args[2])
        );
    }
    if (objClass == "Tomato") {
        p = std::make_unique<Tomato>(
            std::get<double>(args[0]),
            std::get<double>(args[1])
        );
    }
    /*
    if (objClass == ) {
        p = std::make_unique<>(

        );
    }
    */

    if (p) {
        GameObject* raw = p.get();
        pendingObjects.push_back(std::move(p));
        return raw;
    }
    else {
        return nullptr;
    }
}

void Platformer::LoadEntities() {
    objects.clear();
    dyingObjects.clear();
    pendingObjects.clear();
    std::string path = "Levels/";
    path = path + std::to_string(platformer::level) + "/entities.csv";
    std::ifstream file(path);
    std::string line;


    while (std::getline(file, line)) {
        std::stringstream stream(line);
        std::string cell;

        std::string objClass;
        std::getline(stream, objClass, ',');

        std::vector<std::variant<double, std::string>> args;
        while (std::getline(stream, cell, ',')) {
            bool digit = 0;
            if (std::isdigit(cell[0]) || cell[0] == '-') {
                digit = 1;
            }

            if (digit) {
                args.push_back(std::stod(cell));
            }
            else {
                args.push_back(cell);
            }
        }

        AddObject(objClass, args);
    }

    if (autoScroll != 0) {
        double x = player.GetSpawnX();
        double y = player.GetSpawnY();
        AddObject("Lift", { x - 1008-96, 99999.0, autoScroll, y, 0.0, 0.0, 1.0, 1080.0*4 });
        AddObject("Lift", { x + 1008+96, 99999.0, autoScroll, y, 0.0, 0.0, 1.0, 1080.0*4 });
        scrollPos = x;
    }
}


void Platformer::Init() {
    saveP->LoadCurrent(savedata::slot, 1);
    timer.SetTime(platformer::time);
    player.Spawn();
    LoadLevelInfo();
    level.LoadLevel(platformer::level);
    soundsP->PlayMusic(info.BGM);
    objects.push_back(std::make_unique<Toast>(info.name));
    timer.SetTime(platformer::time);
}

void Platformer::Spawn() {
    saveP->LoadProgress(savedata::slot);
    if (platformer::level == 6) {
        autoScroll = 96 * 2;
    }
    else if (platformer::level == 7){
        autoScroll = 96 * 5;
    }
    else {
        autoScroll = 0;
    }
    LoadEntities();
}

void Platformer::Complete() {
    completed = 1;
    soundsP->PlaySE("Complete");
    Mix_HaltMusic();

    for (int i = 0; i < 3; i++) {
        if (savedata::coin[platformer::level - 1][i] | platformer::coin[i]) {
            savedata::coin[platformer::level - 1][i] = 1;
        }
    }
    platformer::coin[0] = 0;
    platformer::coin[1] = 0;
    platformer::coin[2] = 0;

    double time = timer.GetTime();
    complete.SetClearTime(time);
    complete.SetBestTime(savedata::time[platformer::level - 1]);
    complete.levelName = info.name;
    if (savedata::time[platformer::level - 1] > time || savedata::completedLevel[platformer::level-1] != 2) {
        savedata::time[platformer::level - 1] = time;
    }
    complete.SetDeaths(platformer::death);
    
    savedata::completedLevel[platformer::level - 1] = 2;
    platformer::CP = 0;
    platformer::level = 0;
    platformer::time = 0;
    platformer::death = 0;
}

void Platformer::Save() {
    saveP->WriteProgress(savedata::slot);
}

void Platformer::Quit() {
    level.FileOutput(platformer::level);
}

void Platformer::Update() {
    EVENT event = inputP->event;
    OBJRECT screenRect = { (double)settings::baseW / 2, (double)settings::baseH / 2, (double)settings::baseW, (double)settings::baseH, 1 };
    texturesP->DrawRect({ 0,0,0,255 }, screenRect, 0);

    if (!pausing) {
        cameraP->Update();
    }

    //std::cout << timer.GetTime() << std::endl;
    if (!completed) {
        timer.Update();
        platformer::time = timer.GetTime();
        if (!pause.on && !editorMode) scrollPos += settings::timeScale * autoScroll;

        if (savedata::dev) {
            if (event.E) {
                if (editorMode) {
                    editorMode = 0;
                }
                else {
                    editorMode = 1;
                }
            }
            if (event.P) {
                double x, y;
                level.GetMouseC(&x, &y);
                player.SetX(x);
                player.SetY(y);
            }
        }
        

        if (!pause.on) {
            if (inputP->GetEvent(Event::Back)) {
                if (!player.IsDead()) {
                    pause.Init();
                    pause.on = 1;
                }
            }
        }




        if (!editorMode && !pause.on) {
            for (std::unique_ptr<GameObject>& obj : objects) {
                if (inScreen(obj) || obj->alwaysLoad) {
                    obj->Update();
                }
            }
            for (auto& obj : pendingObjects) {
                objects.push_back(std::move(obj));
            }
            pendingObjects.clear();
            objects.erase(
                std::remove_if(objects.begin(), objects.end(),
                    [](const std::unique_ptr<GameObject>& o)
                    {return o->IsDead(); }),
                objects.end()
            );

            player.Update();
        }

        for (auto& obj : objects) {
            EntityType type = obj->GetType();
            if (type == EntityType::BackGround) {
                if (obj->GetLayer() == -1) {
                    obj->Draw();
                }
            }
        }


        level.Update();
        level.DrawMap(editorMode);

        for (auto& obj : objects) {
            EntityType type = obj->GetType();
            if (type != EntityType::BackGround) {
                if (obj->visible) {
                    if (obj->GetLayer() == -1) {
                        obj->Draw();
                    }
                    if (editorMode) obj->DrawHitbox();
                }
            }
        }

        player.Draw();


        for (auto& obj : objects) {
            if (obj->GetLayer() == 1) {
                obj->Draw();
            }
        }
        for (auto& obj : objects) {
            if (obj->GetLayer() == 2) {
                obj->Draw();
            }
        }



        if (editorMode) {
            level.Editor();
        }
        cameraP->Draw();

        coinManager.Update();
        coinManager.Draw();

        pause.Update();
    }
 else {
     complete.Update();
     if (complete.finish) {
         gameP->ChangeScene(Scene::LevelSelect);
         complete.finish = 0;
     }
    }
    
}

bool Platformer::inScreen(std::unique_ptr<GameObject>& p) {
    CAMERA cam = cameraP->GetCam();
    double edgeR, edgeL;
    edgeR = cam.x + settings::baseW / 2 + 192;
    edgeL = cam.x - settings::baseW / 2 - 192;
    OBJRECT rect = p->GetRect();

    if (edgeL < rect.x && rect.x < edgeR) {
        return true;
    }
    return false;
}