#include "ZakoJump.h"
#include "Textures.h"
#include "Sounds.h"
#include "Player.h"

ZakoJump::ZakoJump(double X, double Y) {
    x = X;
    y = Y;
    w = 80;
    h = 96;
    vX = -200;
    time = 0;
    texName = "Bhead";
}

void ZakoJump::Update() {
    timer.Update();
    time = timer.GetTime();

    vY += platformer::gravity * settings::timeScale;
    MoveY();
    CollideY();
    MoveX();
    CollideX();
    if (leftBlock != 0) {
        vX = 200;
    }
    else if (rightBlock != 0) {
        vX = -200;
    }

    if (onGround) {
        vY = 800;
    }
}

void ZakoJump::Draw() {
    texturesP->DrawImage("Bleg", { x - 10,y - 20,70,70 }, 1, {1,sin(time*10) * 32 ,35,8});
    texturesP->DrawImage("Bleg", { x + 10,y - 20,70,70 }, 1, { 1,sin(time * 10) * -32 ,35,8});
    texturesP->DrawImage("Bhead", { x,y + 30,96,96 }, 1, {});
    texturesP->DrawImage("Bface", { x,y + 30,96,96 }, 1, {});
}

void ZakoJump::Touched() {
    playerP->Die();
}

void ZakoJump::Stomped() {
    dead = 1;
    soundsP->PlaySE("1kill");
    playerP->Stomp();
}