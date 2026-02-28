#include "Zako.h"
#include "SDL_mixer.h"
#include "Player.h"
#include "Sounds.h"
#include <iostream>

Zako::Zako(double x0, double y0) {
    texName = "Zako";
    type = EntityType::Zako;
    x = x0;
    y = y0;
    w = 80;
    h = 80;
    vX = -100;
}

void Zako::Update() {
    vY += platformer::gravity * settings::timeScale;
    MoveY();
    CollideY();
    MoveX();
    CollideX();
    if (leftBlock != 0) {
        vX = 100;
    }
    else if (rightBlock != 0) {
        vX = -100;
    }
}


void Zako::Touched() {
    playerP->Die();
}

void Zako::Stomped() {
    dead = 1;
    soundsP->PlaySE("1kill");
    playerP->Stomp();
}