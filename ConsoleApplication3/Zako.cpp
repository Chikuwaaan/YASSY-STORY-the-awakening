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
    w = 96;
    h = 96;
    vX = -150;
    direction = -1;
}

void Zako::Update() {
    vY += platformer::gravity * settings::timeScale;
    MoveY();
    CollideY();
    MoveX();
    CollideX();
    if (leftBlock != 0) {
        direction = 1;
    }
    else if (rightBlock != 0) {
        direction = -1;
    }

    if (direction == 1) {
        vX = 150;
    }
    else if (direction == -1) {
        vX = -150;
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