#include "Coin.h"
#include "Textures.h"
#include "CoinManager.h"

CoinManager* Coin::managerP = nullptr;

Coin::Coin(double X, double Y, double Index) {
    x = X;
    y = Y;
    index = (int)Index;
    texName = "coin";
}

void Coin::Draw() {
    int srcX = 0;
    double a;
    a = std::fmod(timer.GetTime(), 1);

    if (0 <= a && a < 0.25) {
        srcX = 0;
        //color = { 255,255,255,255 };
    }
    else if (0.25 <= a && a < 0.5) {
        srcX = 32;
        //color = { 0,0,0,255 };
    }
    else if (0.5 <= a && a < 0.75) {
        srcX = 64;
        //color = { 255,255,255,255 };
    }
    else if (0.75 <= a && a < 1.0) {
        srcX = 96;
        //color = { 0,0,0,255 };
    }

    texturesP->DrawSprite(texName, { x,y,192,192 }, { srcX,0,32,32 }, 1);
}

void Coin::Touched() {
    managerP->CollectCoin(index);
    dead = 1;
}

void Coin::Stomped() {
    Touched();
}