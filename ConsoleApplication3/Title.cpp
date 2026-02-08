#include "Title.h"
#include <iostream>
#include "UIManager.h"
#include "Textures.h"
#include "OverLay.h"
#include "Game.h"
#include "Input.h"
#include "Options.h"

UIManager* Title::uiP = nullptr;
Textures* Title::texturesP = nullptr;
OverLay* Title::overlayP = nullptr;
Game* Title::gameP = nullptr;
Input* Title::inputP = nullptr;

enum class Phase {
    Loading,
    Logo1,
    Logo2,
    Logo3,
    YassyStory,
    Options
};

Title::Title() :
    back(64, 64, 128, 128)
{
    last = 0;
    timer = 0.0;
    phase = Phase::Loading;
}

void Title::Init() {
    RegisterButtons();
    options.RegisterButtons();
    last = SDL_GetTicks();
    timer = 0.0;
    SDL_SetRenderDrawColor(settings::renderer, 0, 0, 0, 255);
}

void Title::RegisterButtons() {
    uiP->AddButton(&back);
    back.action = [this]() {
        phase = Phase::YassyStory;
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
    else if (phase == Phase::Logo2 && timer > 3.9) {
        phase = Phase::Logo3;
    }
    else if (phase == Phase::Logo3 && timer > 5) {
        phase = Phase::YassyStory;
        overlayP->FadeIn(1, { 0,0,0,255 });
    }
}

void Title::Update() {
    Uint32 now = SDL_GetTicks();
    Uint32 delta = now - last;
    last = now;
    timer += delta / 1000.0;
    ChangePhase();

    SDL_Rect refresh = { 0,0,settings::baseW,settings::baseH };
    SDL_Color white = { 255,255,255,255 };
    SDL_Color black = { 0,0,0,255 };

    if (phase == Phase::Logo1 || phase == Phase::Logo2) {
        SDL_SetRenderDrawColor(settings::renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(settings::renderer, &refresh);
        SDL_Rect sy = texturesP->GetTexRect("studio_yassy");
        sy.x = settings::baseW / 2;
        sy.y = settings::baseH / 2;
        sy.w = sy.w * 8;
        sy.h = sy.h * 8;
        texturesP->DrawImageS("studio_yassy", sy, 0, {});
    }
    if (phase == Phase::Logo3) {
        SDL_SetRenderDrawColor(settings::renderer, 0,0,0, 255);
        SDL_RenderFillRect(settings::renderer, &refresh);
    }
    if (phase == Phase::YassyStory || phase == Phase::Options) {
        SDL_SetRenderDrawColor(settings::renderer, 255,255,255, 255);
        SDL_RenderFillRect(settings::renderer, &refresh);
        SDL_Rect fullScreen = { settings::baseW / 2, settings::baseH / 2, settings::baseW,settings::baseH };
        texturesP->DrawImageS("assy", fullScreen, 0, {});
        texturesP->DrawImageS("title", fullScreen, 0, {});
        if (phase == Phase::YassyStory) {
            //texturesP->DrawTexts("Press any Unco", white, black, { 750,900,1,1 }, 0);
            texturesP->DrawTexts("Press Space Key", white, black, { 960,120,1,1 }, 0, Anchor::Center);
        }

        if (inputP->event.SPACE) {
            phase = Phase::Options;
            
        }
    }

    if (phase == Phase::Options) {
        options.Show();
        options.Update();
        back.state = State::Available;
    }
    else {
        options.Hide();
        back.state = State::Invisible;
    }
    

    uiP->Update();
}