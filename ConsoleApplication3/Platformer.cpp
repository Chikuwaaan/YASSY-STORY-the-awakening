#include "Platformer.h"
#include "Textures.h"
#include "Camera.h"
#include "namespace.h"
#include "GameObject.h"
#include "Lift.h"
#include "Zako.h"

#include <iostream>
#include <fstream>

Textures* Platformer::texturesP = nullptr;
Camera* Platformer::cameraP = nullptr;

Platformer::Platformer() {
    player.levelP = &level;
    GameObject::playerP = &player;
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

        std::vector<double> args;
        while (std::getline(stream, cell, ',')) {
            args.push_back(std::stod(cell));
        }

        if (objClass == "Zako") {
            AddObject<Zako>(args[0], args[1]);
        }
        if (objClass == "Lift") {
            AddObject<Lift>(args[0], args[1], args[2], args[3], args[4], args[5]);
        }
    }
}

void Platformer::Init() {
    level.LoadLevel(platformer::level);
    player.Spawn();
}

void Platformer::Quit() {
    level.FileOutput(platformer::level);
}

void Platformer::Update() {
    OBJRECT screenRect = { (double)settings::baseW / 2, (double)settings::baseH / 2, (double)settings::baseW, (double)settings::baseH, 1 };
    texturesP->DrawRect({ 255,255,255,255 }, screenRect, 0);
    background.Draw();

    cameraP->Update();

    
    for (auto& obj : objects) {
        obj->Update();
        obj->Draw();
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
    
    level.DrawMap();
    player.Update();
    player.Draw();
    //player.DrawPlayer();

    level.Editor();
}
