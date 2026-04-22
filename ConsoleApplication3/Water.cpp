#include "Water.h"
#include "Player.h"
#include "Textures.h"

Water::Water(double X, double Y, double W, double H) {
    x = X + W / 2.0;
    y = Y + H / 2.0;
    w = W;
    h = H;
    texName = "water";
    layer = 1;
}

void Water::Touched() {
    playerP->watering = 1;
}

void Water::Stomped() {
    Touched();
}

void Water::Draw() {
    int i = (int)w / 96;
    double x0 = x - w / 2.0 + 48;
    double y0 = y + h / 2.0 + 48;

    int dstx;
    if ((int)(timer.GetTime()*2) % 2) {
        dstx = 0;
    }
    else {
        dstx = 16;
    }

    for (int j = 0; j < i; j++) {
        texturesP->DrawSprite("water", {x0+j*96, y0, 96, 96}, {dstx, 0, 16, 16}, 1);
    }
    texturesP->DrawSprite("water", {x,y,w,h}, { 32, 0, 16, 16 }, 1);
}