#include "Fan.h"
#include "Textures.h"
#include "Player.h"

Fan::Fan(double X, double Y, double Direction) {
    texName = "fan";
    x = X;
    y = Y;
    w = 96*4;
    h = 960;
    direction = (int)Direction;
}

void Fan::Update() {
    timer1.Update();
    double time = timer1.GetTime();
    if ((int)(time * 4) % 2 == 1) {
        texName = "fan";
    }
    else {
        texName = "fan2";
    }
}

void Fan::Touched() {
    playerP->AddVY(50);
}

void Fan::Stomped() {
    Touched();
}