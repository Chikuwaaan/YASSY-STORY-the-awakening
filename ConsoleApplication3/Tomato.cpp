#include "Tomato.h"
#include "Textures.h"

Tomato::Tomato(double X, double Y) {
    x = X;
    y = Y;
    w = 6;
    h = 6;

    double angle;
    double velocity;
    angle = random.frandom(0, 360);
    velocity = random.frandom(0, 1000);
    vX = cos(utilities::DegreetoRadian(angle)) * velocity;
    vY = sin(utilities::DegreetoRadian(angle)) * velocity;
}

void Tomato::Update() {
    vY += platformer::gravity * settings::timeScale / 2.0;

    if (rightBlock == 0 && leftBlock == 0 && headBlock == 0 && groundBlock == 0) {
        MoveY();
        CollideY();
        MoveX();
        CollideX();
    }
}

void Tomato::Draw() {
    texturesP->DrawRect({255,0,0,255}, {x,y,w,h,1}, 1);
}