#include "Fishy.h"
#include "Player.h"
#include "Textures.h"

Fishy::Fishy(double X, double Y) {
    x = X;
    y = Y;
    w = 96;
    h = 48;

    posX = x;
    amplitudeX = 192;
    vx0 = 96;
    vX = vx0;

    texName = "Fishy";
}

void Fishy::Update() {
    if (posX - x > amplitudeX) {
        vX = vx0;
    }
    else if (x - posX > amplitudeX) {
        vX = vx0 * -1;
    }

    MoveX();
}

void Fishy::Draw() {
    if (vX < 0) {
        texturesP->DrawSprite(texName, { x,y,144,144 }, { 0,0,128,128 }, 1);
    }
    else {
        texturesP->DrawSprite(texName, { x,y,144,144 }, { 128,0,128,128 }, 1);
    }
}

void Fishy::Touched() {
    playerP->Die();
}

void Fishy::Stomped() {
    Touched();
}