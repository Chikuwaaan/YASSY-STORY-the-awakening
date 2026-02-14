#include "Platformer.h"
#include "Textures.h"
#include "Camera.h"
#include "namespace.h"
#include "GameObject.h"
#include "Lift.h"

Textures* Platformer::texturesP = nullptr;
Camera* Platformer::cameraP = nullptr;

Platformer::Platformer() {
    player.levelP = &level;
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

    level.Editor();
}
