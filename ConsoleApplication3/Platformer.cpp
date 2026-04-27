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

#include <iostream>
#include <fstream>
#include <variant>

Textures* Platformer::texturesP = nullptr;
Camera* Platformer::cameraP = nullptr;
Input* Platformer::inputP = nullptr;
Sounds* Platformer::soundsP = nullptr;

Platformer::Platformer() {
    player.levelP = &level;
    Level::playerP = &player;
    GameObject::levelP = &level;
    GameObject::playerP = &player;
    Coin::managerP = &coinManager;
    editorMode = 0;
    pausing = 0;

    pause.back = [this]() {
        pausing = 0;
        };
    pause.SetBackButton();
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
            std::get<double>(args[6])
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
        /*
        if (objClass == "Zako") {
            AddObject<Zako>(std::get<double>(args[0]), std::get<double>(args[1]));
        }
        if (objClass == "Lift") {
            AddObject<Lift>(
                std::get<double>(args[0]),
                std::get<double>(args[1]),
                std::get<double>(args[2]),
                std::get<double>(args[3]),
                std::get<double>(args[4]),
                std::get<double>(args[5]),
                std::get<double>(args[6])
            );
        }
        if (objClass == "LiftFall") {
            AddObject<LiftFall>(
                std::get<double>(args[0]),
                std::get<double>(args[1]),
                std::get<double>(args[2])
            );
        }
        if (objClass == "CheckPoint") {
            AddObject<CheckPoint>(
                std::get<double>(args[0]),
                std::get<double>(args[1]),
                std::get<double>(args[2])
            );
        }
        if (objClass == "BackGround") {
            AddObject<BackGround>(
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
            AddObject<ZakoJump>(
                std::get<double>(args[0]),
                std::get<double>(args[1])
            );
        }
        if (objClass == "JumpPad") {
            AddObject<JumpPad>(
                std::get<double>(args[0]),
                std::get<double>(args[1])
            );
        }
        if (objClass == "Goal") {
            AddObject<Goal>(
                std::get<double>(args[0]),
                std::get<double>(args[1]),
                std::get<double>(args[2]),
                std::get<double>(args[3])
            );
        }
        if (objClass == "Deco") {
            AddObject<Deco>(
                std::get<double>(args[0]),
                std::get<double>(args[1]),
                std::get<double>(args[2]),
                std::get<double>(args[3]),
                std::get<double>(args[4]),
                std::get<std::string>(args[5])
            );
        }
        if (objClass == "Warp") {
            Warp* p0 = AddObject<Warp>(
                std::get<double>(args[0]),
                std::get<double>(args[1]),
                0
            );
            Warp* p1 = AddObject<Warp>(
                std::get<double>(args[2]),
                std::get<double>(args[3]),
                1
            );
            p0->pair = p1;
            p1->pair = p0;
        }
        if (objClass == "Hossy") {
            AddObject<Hossy>(
                std::get<double>(args[0]),
                std::get<double>(args[1])
            );
        }
        if (objClass == "Hosi") {
            AddObject<Hosi>(
                std::get<double>(args[0]),
                std::get<double>(args[1]),
                std::get<double>(args[2])
            );
        }
        if (objClass == "Coin") {
            AddObject<Coin>(
                std::get<double>(args[0]),
                std::get<double>(args[1]),
                std::get<double>(args[2])
            );
        }
        */
    }
}

void Platformer::SaveProgress() {
    savedata::coin = coinManager.GetProgress();
}

void Platformer::Init() {
    LoadLevelInfo();
    level.LoadLevel(platformer::level);
    //cameraP->LoadCameraRoom(platformer::level);
    player.Spawn();
    soundsP->PlayMusic(info.BGM);
    objects.push_back(std::make_unique<Toast>(info.name));
}

void Platformer::Spawn() {
    LoadEntities();
    coinManager.Refresh();
}

void Platformer::Quit() {
    level.FileOutput(platformer::level);
}

void Platformer::Update() {
    EVENT event = inputP->event;
    OBJRECT screenRect = { (double)settings::baseW / 2, (double)settings::baseH / 2, (double)settings::baseW, (double)settings::baseH, 1 };
    texturesP->DrawRect({ 255,255,255,255 }, screenRect, 0);

    if (!pausing) cameraP->Update();

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
    if (event.ESCAPE) {
        if (pausing) {
            pausing = 0;
        }
        else {
            pausing = 1;
        }
    }

    

    if (!editorMode && !pausing) {
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

    texturesP->DrawTexts(std::to_string(timer.GetTime()), { 255,255,255,255 }, { 0,0,0,255 }, { 1700,50,1,1 }, 0, Anchor::Center);

    if (pausing) {
        pause.Update();
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