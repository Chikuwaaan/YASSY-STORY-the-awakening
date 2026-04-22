#include "Water.h"
#include "Player.h"

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