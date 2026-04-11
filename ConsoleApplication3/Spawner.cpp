#include "Spawner.h"
#include "Platformer.h"

Spawner::Spawner() {
    platformerP->AddObject<Zako>(x, y, w, h);
}