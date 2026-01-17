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
    texturesP->DrawTexts("checks point", { 0,0,0,255 }, { x,y+160,1,1 }, 1, {});
}