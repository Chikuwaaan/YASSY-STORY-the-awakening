#include <iostream>
#include <cmath>
#include "Lift.h"
#include "namespace.h"

Lift::Lift(double spawnX, double ampX, double velocityX, double spawnY, double ampY, double velocityY) {
    type = EntityType::Lift;
    h = 96;
    w = 96;
    collision = 1;
    texName = "LIFT";
    x = spawnX;
    y = spawnY;
    posX = spawnX;
    amplitudeX = ampX;
    vX = velocityX;
    posY = spawnY;
    amplitudeY = ampY;
    vY = velocityY;

    vx0 = velocityX;
    vy0 = velocityY;
}

void Lift::Update() {
    if (posX - x > amplitudeX) {
        vX = vx0;
    }
    else if (x - posX > amplitudeX) {
        vX = vx0 * -1;
    }
    
    if (posY - y > amplitudeY) {
        vY = vy0;
    }
    else if (y - posY > amplitudeY) {
        vY = vy0 * -1;
    }
    

    //std::cout << vX << " " << vY << std::endl;
    MoveX();
    MoveY();
}