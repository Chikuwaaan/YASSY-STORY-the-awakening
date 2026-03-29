#include "Warp.h"
#include "Textures.h"
#include "Player.h"
#include "Sounds.h"

Warp::Warp(double X, double Y, int i) {
    x = X;
    y = Y;
    w = 144;
    h = 144;
    index = i;
    interval = 0;
    on = true;
}

void Warp::Update() {
    timerI.Update();
    if (timerI.GetTime() >= interval) {
        on = true;
    }
    else {
        on = false;
    }
}

void Warp::Draw() {
    timer.Update();
    double time;
    time = timer.GetTime();

    SDL_Color color = { 255,255,255,255 };
    int srcX = 0;
    int srcY;
    if (on) {
        srcY = 0;
    }
    else {
        srcY = 32;
    }
    double a;
    a = std::fmod(time, 1);

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

    texturesP->DrawSprite("warpstar", {x,y,192,192}, {srcX,srcY,32,32},1);
}

void Warp::Touched() {
    if (timerI.GetTime() >= interval) {
        soundsP->PlaySE("warp");
        interval = 2;
        pair->interval = interval;
        OBJRECT dst = pair->GetRect();
        playerP->SetX(dst.x);
        playerP->SetY(dst.y);
        timerI.Reset();
        pair->timerI.Reset();
    }
}

void Warp::Stomped() {
    Touched();
}