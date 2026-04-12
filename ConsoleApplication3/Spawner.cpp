#include "Spawner.h"
#include "Platformer.h"

Spawner::Spawner(std::string tex, std::vector<std::variant<double, std::string>> Args) {
    Class = std::get<std::string>(Args[1]);
    interval = std::get<double>(Args[0]);
    Args.erase(Args.begin());
    Args.erase(Args.begin());
    args = Args;
    x = std::get<double>(Args[0]);
    y = std::get<double>(Args[1]);
    w = 96;
    h = 96;
    layer = 1;
    texName = tex;

    platformerP->AddObject(Class, args);
}

void Spawner::Update() {
    timer.Update();
    if (timer.GetTime() > interval) {
        platformerP->AddObject(Class, args);
        timer.Reset();
    }
}