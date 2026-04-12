#include "Hossy.h"
#include "Textures.h"
#include "Player.h"
#include "Platformer.h"
#include "Hosi.h"
#include "Sounds.h"

Hossy::Hossy(double X, double Y) {
    x = X;
    y = Y;
    w = 60;
    h = 60;
    texName = "Hossy";
    angle = 0;
    exproding = 0;
}

void Hossy::Update() {
    timerSpin.Update();
    angle = sin(timerSpin.GetTime() * 5) * 20;

    OBJRECT rectP = playerP->GetRect();
    double dx = rectP.x - x;
    double dy = rectP.y - y;
    double sqDistance = dx * dx + dy * dy;

    if (sqDistance <= 250000) {
        exproding = 1;
    }
    if (exproding) {
        angle = sin(timerSpin.GetTime() * 5) * 200;
        timerExprode.Update();
        if (timerExprode.GetTime() >= 0.5) {
            dead = 1;
            for (int i = 18; i < 360; i += 72) {
                platformerP->AddObject("Hosi", { x, y, (double)i });
            }
        }
    }
    
}

void Hossy::Draw() {
    texturesP->DrawImage(texName, { x,y,96,96 }, 1, { 1, angle, 48,48 });
}

void Hossy::Touched() {
    playerP->Die();
}

void Hossy::Stomped() {
    dead = 1;
    soundsP->PlaySE("1kill");
    playerP->Stomp();
}