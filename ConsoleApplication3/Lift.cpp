#include <iostream>
#include <cmath>
#include "Lift.h"
#include "namespace.h"

Lift::Lift(double spawnX, double ampX, double velocityX, double spawnY, double ampY, double velocityY) {
    type = entityType::Lift;
    h = 1000;
    w = 400;
    collision = 1;
    texName = "unko";
    x = spawnX;
    y = spawnY;
    posX = spawnX;
    amplitudeX = ampX;
    vX = velocityX;
    posY = spawnY;
    amplitudeY = ampY;
    vY = velocityY;

}

void Lift::Update() {
    if (posX - x > amplitudeX) {
        vX = vX * -1;
    }
    else if (x - posX > amplitudeX) {
        vX = vX * -1;
    }
    
    if (posY - y > amplitudeY) {
        vY = vY * -1;
    }
    else if (y - posY > amplitudeY) {
        vY = vY * -1;
    }
    

    //std::cout << vX << " " << vY << std::endl;
    MoveX();
    MoveY();
}