#include "Coco.h"
#include "Textures.h"
#include "Sounds.h"
#include "Player.h"
#include "Rand.h"

Coco::Coco(double X, double Y) {
    x = X;
    y = Y;
    w = 60;
    h = 60;
    texName = "Coco";

    Rand random;
    vX = random.frandom(-192, 192);
    vY = 0;

    falling = 0;
}

void Coco::Update() {
    double pX = playerP->GetRect().x;
    double dX = pX - x;

    if (!falling) {
        if (-192 <= dX && dX <= 192) {
            falling = 1;
            soundsP->PlaySE("fall");
        }
    }
    

    if (falling) {
        vY += platformer::gravity * settings::timeScale;
        MoveX();
        MoveY();
        if (y < 0) dead = 1;
    }
}

void Coco::Draw() {
    texturesP->DrawImage(texName, {x,y,70,70}, 1, {});
}

void Coco::Touched() {
    playerP->Die();
}

void Coco::Stomped() {
    dead = 1;
    soundsP->PlaySE("1kill");
    playerP->Stomp();
}