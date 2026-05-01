#include "Coin.h"
#include "Textures.h"
#include "CoinManager.h"
#include "Sounds.h"

CoinManager* Coin::managerP = nullptr;

Coin::Coin(double X, double Y, double Index) {
    x = X;
    y = Y;
    vX = random.frandom(-100, 100);
    index = (int)Index;
    texName = "coin";
    anim = 0;
    
    if (savedata::coin[platformer::level-1][index] == 1) {
        platformer::coin[index] = 2;
    }
    else {
        isCollected = 0;
    }

}

void Coin::Update() {
    if (anim) {
        GameTimer.Update();
        vY += platformer::gravity * settings::timeScale;
        MoveX();
        MoveY();
    }
    if (GameTimer.GetTime() > 2) {
        dead = 1;
    }
}

void Coin::Draw() {
    //if (isCollected) return;

    int srcX = 0;
    int srcY = 0;
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

    if (platformer::coin[index] == 2) {
        srcY = 32;
    }

    texturesP->DrawSprite(texName, { x,y,192,192 }, { srcX,srcY,32,32 }, 1);
}

void Coin::Touched() {
    if (!isCollected) {
        managerP->CollectCoin(index);
        isCollected = 1;
        soundsP->PlaySE("coin");
        anim = 1;
        vY = 1000;
    }
}

void Coin::Stomped() {
    Touched();
}