#include "JumpPad.h"
#include "Player.h"
#include "Textures.h"
#include "Sounds.h"

JumpPad::JumpPad(double X, double Y) {
    x = X;
    y = Y;
    w = 288;
    h = 32;
    texName = "flower";
}

void JumpPad::Update() {
    timer.Update();
    double time = timer.GetTime();
    if ((int)(time*2) % 2 == 1) {
        texName = "flower";
    }
    else {
        texName = "flower2";
    }
}

void JumpPad::Touched() {
    playerP->JumpPadded(1500);
    soundsP->PlaySE("boin");
}

void JumpPad::Stomped() {
    Touched();
}

void JumpPad::Draw() {
    texturesP->DrawImage(texName, { x,y,w,96 }, 1, {});
}