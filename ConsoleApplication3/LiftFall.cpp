#include "LiftFall.h"
#include "Textures.h"
#include "Player.h"
#include <iostream>

LiftFall::LiftFall(double X, double Y, double L) {
    type = EntityType::LiftFall;
    texName = "Lift";
    alwaysLoad = 1;
    x = X;
    y = Y;
    w = 96 * L;
    h = 96;
    x0 = X;
    y0 = Y;
    length = L;
    collision = true;
    isFalling = false;
    respawning = 0;
}

void LiftFall::Update() {
    if (isFalling) {
        vY += settings::timeScale * platformer::gravity * 0.5;
        MoveY();
    }

    if (y <= 0 && !respawning) {
        respawning = 1;
        isFalling = 0;
        x = x0;
        y = y0;
        vY = 0;
        timer.Reset();
        collision = 0;
    }

    timer.Update();
    double time = timer.GetTime();
    if (respawning) {
        if (time > 3.0 && !utilities::HitDetection(playerP->GetRect(), {x,y,w,h})) {
            respawning = 0;
            collision = 1;
        }
    }
}

void LiftFall::Stomped() {
    if (!respawning) {
        isFalling = true;
    }
}

void LiftFall::Draw() {
    int srcY = 0;

    if (isFalling) {
        srcY = 16;
    }
    else if (respawning) {
        double time = timer.GetTime();
        if (time < 1) {
            srcY = 999;
        }
        else if (time < 2.6) {
            srcY = 32;
        }
        else {
            srcY = 48;
        }
    }

    double a = (length - 1) / 2.0;
    double xL = (x - a * h);
    double xR = (x + a * h);
    OBJRECT dstL = { xL,y,h,h };
    OBJRECT dstR = { xR,y,h,h };
    texturesP->DrawSprite(texName, dstL, { 0,srcY,16,16 }, 1);
    texturesP->DrawSprite(texName, dstR, { 32,srcY,16,16 }, 1);

    //drawM
    OBJRECT dstM;
    dstM.x = xL;
    dstM.y = y;
    dstM.w = h;
    dstM.h = h;
    for (int i = 0; i < length - 2; i++) {
        dstM.x += h;
        texturesP->DrawSprite(texName, dstM, { 16,srcY,16,16 }, 1);
    }
}