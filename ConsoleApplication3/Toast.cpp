#include "Toast.h"
#include "Textures.h"

Toast::Toast(std::u8string Text) {
    text = Text;
    x = 1920;
    y = 96;
    w = 1920;
    h = 192;
    alwaysLoad = 1;
    layer = 2;
    phase = PHASE::appear;
}

void Toast::Update() {
    if (phase == PHASE::appear) {
        x = 1920 - timer.GetTime() * 1000;
        if (x < 960) {
            x = 960;
            phase = PHASE::stay;
            timer.Reset();
        }
    }

    if (phase == PHASE::stay) {
        if (timer.GetTime() > 3.0) {
            phase = PHASE::disappear;
            timer.Reset();
        }
    }

    if (phase == PHASE::disappear) {
        x = 960 + timer.GetTime() * 1000;
        if (x > 1920) {
            dead = 1;
        }
    }
}

void Toast::Draw() {
    SDL_Color white = { 255,255,255,255 };
    texturesP->DrawImageA("toast", {x,y,w,h}, 0, Anchor::Left);
    texturesP->DrawImage("whitestar", { x+160,y,128,128 }, 0, {1,star.GetTime()*120,64,64});
    texturesP->DrawTexts(text, white, { 0,0,0,1 }, {x+250,y,1.5,1.5}, 0, Anchor::Left);
}