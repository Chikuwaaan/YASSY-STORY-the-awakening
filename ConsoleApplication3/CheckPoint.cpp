#include "CheckPoint.h"
#include "Player.h"
#include "Textures.h"
#include "Sounds.h"

CheckPoint::CheckPoint(double x0, double y0, double Index) {
    texName = "cp";
    x = x0;
    y = y0;
    w = 60;
    h = 96;

    used = 0;
    index = (int)Index;

    if (index == 0) {
        used = 1;
        //visible = 0;
    }
    if (index == playerP->currentCP) {
        playerP->SetSpawnPoint(x, y);
    }
}

void CheckPoint::Update() {
    if (!used) {
        if (playerP->currentCP >= index) {
            used = 1;
        }
    }
}

void CheckPoint::Touched() {
    if (!used) {
        playerP->currentCP = index;
        playerP->Save();
        used = 1;
        soundsP->PlaySE("cp");
    }
}

void CheckPoint::Stomped() {
    Touched();
}

void CheckPoint::Draw() {
    if (index != 0) {
        SDL_Rect src;
        if (!used) {
            texturesP->DrawTexts(u8"チェック ポイント", { 255,255,255,255 }, { 0,0,0,255 }, { x,y + 80,0.8,0.8 }, 1, Anchor::Center);
            texturesP->DrawTexts(u8"ス", { 255,255,255,15 }, { 0,0,0,15 }, { x - 5,y + 70,0.4,0.4 }, 1, Anchor::Center);
            src = { 0,0,16,16 };
        }
        else {
            OBJRECT pRect = playerP->GetRect();
            if (pRect.x < x) {
                src = { 16,0,16,16 };
            }
            else {
                src = { 32,0,16,16 };
            }
        }
        texturesP->DrawSprite(texName, { x,y,h,h }, src, 1);
    }
    else {
        OBJRECT rect = { x,y+48,192,192 };
        texturesP->DrawImage("signR", rect, 1, {});
    }
    
}