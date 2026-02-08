#include "CheckPoint.h"
#include "Player.h"
#include "Textures.h"

CheckPoint::CheckPoint() {
    x = 10720;
    y = 640;
    w = 160;
    h = 160;
    texName = "cp";
}

void CheckPoint::Touched() {
    playerP->SetSpawnPoint(x, y);
    dead = 1;
}

void CheckPoint::Update() {
}