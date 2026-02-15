#include "Title.h"
#include <iostream>
#include "UIManager.h"
#include "Textures.h"
#include "OverLay.h"
#include "Game.h"
#include "Input.h"
#include "Options.h"

Textures* Title::texturesP = nullptr;
OverLay* Title::overlayP = nullptr;
Game* Title::gameP = nullptr;
Input* Title::inputP = nullptr;

enum class Phase {
    Loading,
    Logo1,
    Logo2,
    Logo3,
    YassyStory1,
    YassyStory2,
    Options
};

Title::Title() :
    BTNback(224, 204, 128, 128),
    BTNstart(960, 540, 512, 128),
    BTNoptions(960, 340, 512, 128),
    BTNexitgame(960, 140, 512, 128)
{
    last = 0;
    timer = 0.0;
    phase = Phase::YassyStory1;
}

void Title::Init() {
    RegisterButtons();
    options.RegisterButtons();
    last = SDL_GetTicks();
    timer = 0.0;
    SDL_SetRenderDrawColor(settings::renderer, 0, 0, 0, 255);
}

void Title::RegisterButtons() {
    ui.AddButton(&BTNback);
    BTNback.icon = Icons::Back;
    BTNback.action = [this]() {
        phase = Phase::YassyStory2;
        };

    ui.AddButton(&BTNstart);
    BTNstart.text = "START";
    BTNstart.action = []() {
        gameP->ChangeScene(Scene::LevelSelect);
        };

    ui.AddButton(&BTNoptions);
    BTNoptions.text = "OPTIONS";
    BTNoptions.action = [this]() {
        phase = Phase::Options;
        };

    ui.AddButton(&BTNexitgame);
    BTNexitgame.text = "EXIT";
    BTNexitgame.action = []() {
        gameP->ExitGame();
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
        phase = Phase::YassyStory1;
        overlayP->FadeIn(1, { 0,0,0,255 });
        Mix_Music* music = Mix_LoadMUS("Assets/sounds/toilet3.wav");
        Mix_PlayMusic(music, -1);
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
    if (phase == Phase::YassyStory1 || phase == Phase::YassyStory2 || phase == Phase::Options) {
        SDL_SetRenderDrawColor(settings::renderer, 255,255,255, 255);
        SDL_RenderFillRect(settings::renderer, &refresh);
        SDL_Rect fullScreen = { settings::baseW / 2, settings::baseH / 2, settings::baseW,settings::baseH };
        
        texturesP->DrawImageS("room", fullScreen, 0, {});
        if (phase == Phase::YassyStory2 || phase == Phase::Options) {
            texturesP->DrawImageS("title", { settings::baseW / 2,settings::baseH * 3 / 4 , settings::baseW/2, settings::baseH/2}, 0, {});
        }
        else {
            texturesP->DrawImageS("title", fullScreen, 0, {});
        }

        if (phase == Phase::YassyStory1) {
            texturesP->DrawTexts("Press Space Key", white, black, { 960,120,1,1 }, 0, Anchor::Center);
        }

        if (inputP->event.SPACE) {
            phase = Phase::YassyStory2;
            options.Show();
        }
    }

    if (phase == Phase::YassyStory2) {
        BTNstart.visible = true;
        BTNoptions.visible = true;
        BTNexitgame.visible = true;

        BTNstart.state = State::Idle;
        BTNoptions.state = State::Idle;
        BTNexitgame.state = State::Idle;
    }
    else {
        BTNstart.visible = false;
        BTNoptions.visible = false;
        BTNexitgame.visible = false;
    }

    if (phase == Phase::Options) {
        BTNback.visible = true;
        BTNback.state = State::Idle;
        options.Show();
        options.Update();
    }
    else {
        BTNback.visible = false;
        options.Hide();
    }
    

    ui.Update();
}