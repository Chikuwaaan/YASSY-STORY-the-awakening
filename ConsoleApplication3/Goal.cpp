#include "Goal.h"
#include "Player.h"

Goal::Goal(double X, double Y, double W, double H) {
    x = X;
    y = Y;
    w = W;
    h = H;
}

void Goal::Touched() {
    playerP->Goal();
}

void Goal::Stomped() {
    Touched();
}