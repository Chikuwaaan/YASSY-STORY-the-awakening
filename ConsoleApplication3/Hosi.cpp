#include "Hosi.h"
#include <iostream>
#include "Player.h"

Hosi::Hosi(double X, double Y, double Angle) {
    x = X;
    y = Y;
    w = 32;
    h = 32;
    texName = "Hossy";
    angle = Angle;
    vX = cos(utilities::DegreetoRadian(angle)) * 500;
    vY = sin(utilities::DegreetoRadian(angle)) * 500;
    
}

void Hosi::Update() {
    MoveX();
    MoveY();
    timer.Update();
    if (timer.GetTime() >= 2) {
        dead = 1;
    }
}

void Hosi::Touched() {
    playerP->Die();
}

void Hosi::Stomped() {
    Touched();
}