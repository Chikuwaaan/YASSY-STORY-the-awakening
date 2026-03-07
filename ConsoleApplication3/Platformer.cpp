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

#include <iostream>
#include <fstream>
#include <variant>

Textures* Platformer::texturesP = nullptr;
Camera* Platformer::cameraP = nullptr;
Input* Platformer::inputP = nullptr;
Sounds* Platformer::soundsP = nullptr;

Platformer::Platformer() {
    player.levelP = &level;
    GameObject::levelP = &level;
    GameObject::playerP = &player;

    editorMode = 0;
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
            bool digit  = 0;
            if (std::isdigit(cell[0])) {
                digit = 1;
            }

            if (digit) {
                args.push_back(std::stod(cell));
            }
            else {
                args.push_back(cell);
            }
        }

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
            /*
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
            */
            objects.push_back(std::make_unique<BackGround>(480, 2496, 1, 1, 1440, 3036, 1, "leaves"));
        }
    }
}

void Platformer::Init() {
    LoadLevelInfo();
    level.LoadLevel(platformer::level);
    //cameraP->LoadCameraRoom(platformer::level);
    player.Spawn();
    soundsP->PlayMusic(info.BGM);
    objects.push_back(std::make_unique<Toast>(info.name));
}

void Platformer::Quit() {
    level.FileOutput(platformer::level);
}

void Platformer::Update() {
    EVENT event = inputP->event;
    OBJRECT screenRect = { (double)settings::baseW / 2, (double)settings::baseH / 2, (double)settings::baseW, (double)settings::baseH, 1 };
    texturesP->DrawRect({ 255,255,255,255 }, screenRect, 0);

    cameraP->Update();

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

    if (!editorMode) {
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
    level.DrawMap();

    for (auto& obj : objects) {
        EntityType type = obj->GetType();
        if (type != EntityType::BackGround) {
            if (obj->visible) {
                obj->Draw();
            }
        }
    }
    
    player.Draw();

    
    for (auto& obj : objects) {
        EntityType type = obj->GetType();
        if (type == EntityType::BackGround) {
            if (obj->GetLayer() == 1) {
                obj->Draw();
            }
        }
    }
    

    if (editorMode) {
        level.Editor();
    }
    cameraP->Draw();

    texturesP->DrawTexts(std::to_string(timer.GetTime()), { 255,255,255,255 }, { 0,0,0,255 }, { 1700,50,1,1 }, 0, Anchor::Center);
}

bool Platformer::inScreen(std::unique_ptr<GameObject>& p) {
    CAMERA cam = cameraP->GetCam();
    double edgeR, edgeL;
    edgeR = cam.x + settings::baseW/2 + 192;
    edgeL = cam.x - settings::baseW/2 - 192;
    OBJRECT rect = p->GetRect();

    if (edgeL < rect.x && rect.x < edgeR) {
        return true;
    } 
    return false;
}