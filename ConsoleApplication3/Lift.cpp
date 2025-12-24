#include <iostream>
#include <cmath>
#include "Lift.h"
#include "namespace.h"

Lift::Lift(double spawnX, double spawnY, double amp, double velocity) {
    type = entityType::Lift;
    h = 80;
    w = 80;
    collision = { 0,1,0,0 };
    texName = "ssk";
    x = spawnX;
    y = spawnY;
    posX = spawnX;
    posY = spawnY;
    amplitude = amp;
    vY = velocity;

}

void Lift::Update() {
    MoveY();

    
    if (posY - y > amplitude) {
        vY = vY * -1;
    }
    else if (y - posY > amplitude) {
        vY = vY * -1;
    }
    
}