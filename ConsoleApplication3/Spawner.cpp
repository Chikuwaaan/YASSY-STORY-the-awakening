#include "Spawner.h"
#include "Platformer.h"

Spawner::Spawner(double X, double Y) {
    x = X;
    y = Y;
    w = 96;
    h = 96;
    layer = 1;
}

void Spawner::Update() {
    timer.Update();
    if (timer.GetTime() > 1) {
        platformerP->AddObject("Zako", { x,y });
        timer.Reset();
    }
}