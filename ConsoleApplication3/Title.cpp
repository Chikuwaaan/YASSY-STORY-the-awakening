#include "Title.h"
#include <iostream>
#include "UIManager.h"
#include "Textures.h"
#include "OverLay.h"
#include "Game.h"

UIManager* Title::uiP = nullptr;
Textures* Title::texturesP = nullptr;
OverLay* Title::overlayP = nullptr;
Game* Title::gameP = nullptr;

enum class Phase {
    Loading,
    Logo1,
    Logo2,
    unc
};

Title::Title() :
    button1(64, 64, 128, 128)
{
    last = 0;
    timer = 0.0;
    phase = Phase::Loading;
}

void Title::Init() {
    //RegisterButtons();
    last = SDL_GetTicks();
}

void Title::RegisterButtons() {
    uiP->AddButton(&button1);
    button1.action = []() {
        std::cout << "‚Û‚¿";
        };
}

void Title::ChangePhase() {
    if (phase == Phase::Loading && timer > 0) {
        phase = Phase::Logo1;
    }
    else if (phase == Phase::Logo1 && timer > 3) {
        phase = Phase::Logo2;
        overlayP->FadeOut(1, { 0,0,0,255 });
    }
    else if (phase == Phase::Logo2 && timer > 4) {
        phase = Phase::unc;
    }
}

void Title::Update() {
    Uint32 now = SDL_GetTicks();
    Uint32 delta = now - last;
    last = now;
    timer += delta / 1000.0;
    ChangePhase();

    SDL_Renderer* r = settings::renderer;
    SDL_Rect refresh = { 0,0,settings::baseW,settings::baseH };
    SDL_SetRenderDrawColor(r, 0,0,0, 255);
    SDL_RenderFillRect(r, &refresh);

    if (phase == Phase::Logo1 || phase == Phase::Logo2) {
        SDL_Rect sy = texturesP->GetTexRect("studio_yassy");
        sy.x = settings::baseW / 2;
        sy.y = settings::baseH / 2;
        sy.w = sy.w * 8;
        sy.h = sy.h * 8;
        texturesP->DrawImageS("studio_yassy", sy, 0, {});
    }
    if (phase == Phase::unc) {
        gameP->ChangeScene(Scene::Platformer);
        return;
    }
    

    uiP->Update();
}