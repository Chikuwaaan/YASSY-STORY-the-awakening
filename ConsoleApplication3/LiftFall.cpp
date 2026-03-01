#include "LiftFall.h"
#include <iostream>

LiftFall::LiftFall(double X, double Y) {
    texName = "LIFT";
    x = X;
    y = Y;
    w = 96;
    h = 96;
    collision = true;
    isFalling = false;
}

void LiftFall::Update() {
    if (isFalling) {
        vY -= settings::timeScale * platformer::gravity * -0.5;
        MoveY();
    }
    if (y <= 0) {
        dead = true;
    }
}

void LiftFall::Stomped() {
    isFalling = true;
}