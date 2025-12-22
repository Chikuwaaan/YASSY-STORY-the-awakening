#include <iostream>
#include <cmath>
#include "Lift.h"
#include "namespace.h"

Lift::Lift(double spawnX, double spawnY, int initialDirection) {
    texName = "5";
    x = spawnX;
    y = spawnY;
    posX = spawnX;
    posY = spawnY;
    direction = initialDirection;
    amplitude = 80;
    speed = 80;
}

void Lift::Update() {
    vX = speed * direction;
    MoveX();

    if (std::abs(x - posX) >= amplitude) {
        x = posX + (amplitude - 1) * direction;
        direction = direction * -1;
    }
    
}