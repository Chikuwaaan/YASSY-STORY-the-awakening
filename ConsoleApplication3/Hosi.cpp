#include "Hosi.h"
#include <iostream>
#include "Textures.h"
#include "Player.h"

Hosi::Hosi(double X, double Y, double Angle) {
    x = X;
    y = Y;
    w = 32;
    h = 32;
    texName = "Hossy";
    angle = Angle;
    vX = cos(utilities::DegreetoRadian(angle)) * 300;
    vY = sin(utilities::DegreetoRadian(angle)) * 300;
    
}

void Hosi::Update() {
    MoveX();
    MoveY();
    timer.Update();
    if (timer.GetTime() >= 2) {
        dead = 1;
    }
}

void Hosi::Draw() {
    texturesP->DrawImage(texName, { x,y,w * 2,h * 2 }, 1, {});
}

void Hosi::Touched() {
    playerP->Die();
}

void Hosi::Stomped() {
    Touched();
}