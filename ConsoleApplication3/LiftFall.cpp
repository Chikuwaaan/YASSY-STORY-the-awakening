#include "LiftFall.h"
#include <iostream>

LiftFall::LiftFall(double X, double Y) {
    x = X;
    y = Y;
    w = 96;
    h = 96;
    collision = true;
    isFalling = false;
}

void LiftFall::Update() {
    if (isFalling && 0) {
        vY -= settings::timeScale * 500;
        MoveY();
    }
    if (y <= 0) {
        dead = true;
    }
}

void LiftFall::Stomped() {
    isFalling = true;
    std::cout << "uo";
}

void LiftFall::Touched() {
    isFalling = true;
    std::cout << "UO";
}