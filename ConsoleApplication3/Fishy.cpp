#include "Fishy.h"
#include "Player.h"
#include "Textures.h"
#include "Sounds.h"
#include "Platformer.h"

Fishy::Fishy(double X, double Y, double Type) {
    type = (int)Type;
    x = X;
    y = Y;
    if (type == 1) {
        w = 96;
        h = 48;
    }
    else if (type == 2) {
        w = 48;
        h = 96;
    }
    

    posX = x;
    amplitudeX = 192;
    vx0 = 96;
    vX = vx0;
    y0 = Y;
    

    texName = "Fishy";
    alwaysLoad = 1;
}

void Fishy::Update() {
    if (type == 1) {
        if (posX - x > amplitudeX) {
            vX = vx0;
        }
        else if (x - posX > amplitudeX) {
            vX = vx0 * -1;
        }
        MoveX();
    }
    if (type == 2) {
        vY += platformer::gravity * settings::timeScale;
        if (y <= y0) {
            vY = 1600;
            y = y0;
            platformerP->AddObject("Particle", { x, y+40, "splash" });
            platformerP->AddObject("Particle", { x, y+40, "splash" });
            platformerP->AddObject("Particle", { x, y+40, "splash" });
            platformerP->AddObject("Particle", { x, y+40, "splash" });
        }
        MoveY();
    }
}

void Fishy::Draw() {
    if (type == 1) {
        if (vX < 0) {
            texturesP->DrawSprite(texName, { x,y,144,144 }, { 0,0,128,128 }, 1);
        }
        else {
            texturesP->DrawSprite(texName, { x,y,144,144 }, { 128,0,128,128 }, 1);
        }
    }
    if (type == 2) {
        if (vY < 0) {
            texturesP->DrawSprite(texName, { x,y,144,144 }, { 128,128,128,128 }, 1);
        }
        else {
            texturesP->DrawSprite(texName, { x,y,144,144 }, { 0,128,128,128 }, 1);
        }
    }
}

void Fishy::Touched() {
    playerP->Die();
}

void Fishy::Stomped() {
    dead = 1;
    soundsP->PlaySE("1kill");
    playerP->Stomp();
}