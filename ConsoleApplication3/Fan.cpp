#include "Fan.h"
#include "Textures.h"
#include "Player.h"
#include "Platformer.h"

Fan::Fan(double X, double Y, double Direction) {
    texName = "fan";
    x = X+144;
    y = Y+240;
    w = 96*4;
    h = 576;
    direction = (int)Direction;
}

void Fan::Update() {
    timer1.Update();
    double time = timer1.GetTime();
    if ((int)(time * 16) % 2 == 1) {
        texName = "fan";
    }
    else {
        texName = "fan2";
    }

    if (direction == 1) {
        platformerP->AddObject("Particle", { x, y - 240, "wind1" });
    }
    else if (direction == 3) {
        platformerP->AddObject("Particle", { x, y + 240, "wind3" });
    }
    
}

void Fan::Touched() {
    if (direction == 1) {
        playerP->AddVY(48);
    }
    else if (direction == 3) {
        playerP->AddVY(-10);
    }
    
}

void Fan::Stomped() {
    Touched();
}

void Fan::Draw() {
    if (direction == 1) {
        texturesP->DrawImage(texName, { x, y - 240, 384, 96 }, 1, {});
    }
    else if (direction == 3) {
        texturesP->DrawImage(texName, { x, y + 240, 384, 96 }, 1, {0,0,0,0,0,1});
    }
    
}