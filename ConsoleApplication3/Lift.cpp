#include <iostream>
#include <cmath>
#include "Lift.h"
#include "namespace.h"
#include "Textures.h"

Lift::Lift(double spawnX, double ampX, double velocityX, double spawnY, double ampY, double velocityY, double L, double H) {
    type = EntityType::Lift;
    h = H;
    w = 96 * L;
    collision = 1;
    texName = "Lift";
    x = spawnX;
    y = spawnY;
    posX = spawnX;
    amplitudeX = ampX;
    vX = velocityX;
    posY = spawnY;
    amplitudeY = ampY;
    vY = velocityY;
    length = L;

    vx0 = abs(velocityX);
    vy0 = abs(velocityY);
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
/*
void Lift::Draw() {
    int srcY = 64;
    double a = (length - 1) / 2.0;
    double xL = (x - a * h);
    double xR = (x + a * h);
    OBJRECT dstL = { xL,y,h,h };
    OBJRECT dstR = { xR,y,h,h };
    texturesP->DrawSprite(texName, dstL, { 0,srcY,16,16 }, 1);
    texturesP->DrawSprite(texName, dstR, { 32,srcY,16,16 }, 1);

    //drawM
    OBJRECT dstM;
    dstM.x = xL;
    dstM.y = y;
    dstM.w = h;
    dstM.h = h;
    for (int i = 0; i < length - 2; i++) {
        dstM.x += h;
        texturesP->DrawSprite(texName, dstM, { 16,srcY,16,16 }, 1);
    }
}
*/