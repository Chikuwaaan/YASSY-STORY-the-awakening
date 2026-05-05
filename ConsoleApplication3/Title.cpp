#include "Title.h"
#include <iostream>
#include "UIManager.h"
#include "Textures.h"
#include "OverLay.h"
#include "Game.h"
#include "Input.h"
#include "Options.h"
#include "Sounds.h"

Textures* Title::texturesP = nullptr;
OverLay* Title::overlayP = nullptr;
Game* Title::gameP = nullptr;
Input* Title::inputP = nullptr;
Sounds* Title::soundsP = nullptr;

enum class Phase {
    Loading,
    Logo1,
    Logo2,
    Logo3,
    YassyStory1,
    YassyStory2,
    Options,
    Credits
};

Title::Title() :
    BTNstart(960, 550, 512, 128),
    BTNoptions(960, 400, 512, 128),
    BTNcredits(960, 250, 512, 128),
    BTNexitgame(960, 100, 512, 128),
    BTNface(5,1075,10,10),
    BTNback(96, 96, 192, 192)
{
    last = 0;
    timer = 0.0;
    //phase = Phase::Options;
    phase = Phase::YassyStory2;
    //phase = Phase::Loading;
}

void Title::Init() {
    RegisterButtons();
    options.RegisterButtons();
    last = SDL_GetTicks();
    timer = 0.0;
    SDL_SetRenderDrawColor(settings::renderer, 0, 0, 0, 255);
}

void Title::RegisterButtons() {
    titleMenu = {
        {&BTNstart, &BTNoptions, &BTNcredits, &BTNexitgame},
        DIRECTION::V,
        nullptr,
        nullptr
    };
    face = {
        {&BTNface, &BTNback}
    };
    ui.AddLine(&titleMenu);
    uiCredits.AddLine(&face);
    ui.currentLine = &titleMenu;

    BTNstart.text = "START";
    BTNstart.action = []() {
        gameP->ChangeScene(Scene::SlotSelect);
        overlayP->FadeOut(1,{0,0,0,255});
        };

    BTNoptions.text = "OPTIONS";
    BTNoptions.action = [this]() {
        phase = Phase::Options;
        };

    BTNcredits.text = "CREDITS";
    BTNcredits.action = [this]() {
        phase = Phase::Credits;
        };

    BTNexitgame.text = "EXIT";
    BTNexitgame.action = []() {
        gameP->ExitGame();
        };

    BTNface.icon = Icons::UO;
    BTNface.action = [this]() {
        this->gameP->ChangeScene(Scene::FaceYassy);
        };

    options.BTNback.action = [this]() {
        phase = Phase::YassyStory2;
        };

    BTNback.icon = Icons::Back;
    BTNback.action = [this]() {
        phase = Phase::YassyStory2;
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
        soundsP->PlayMusic("toilet3");
    }
}

void Title::Update() {
    Uint32 now = SDL_GetTicks();
    Uint32 delta = now - last;
    last = now;
    timer += delta / 1000.0;
    ChangePhase();

    SDL_Rect fullScreen = { settings::baseW / 2, settings::baseH / 2, settings::baseW,settings::baseH };
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
        
        
        texturesP->DrawImageS("IMG_20260206_233135", fullScreen, 0, {});
        if (phase == Phase::YassyStory2 || phase == Phase::Options) {
            texturesP->DrawImageS("title", { settings::baseW / 2,settings::baseH * 3 / 4 , settings::baseW/2, settings::baseH/2}, 0, {});
        }
        else {
            texturesP->DrawImageS("title", fullScreen, 0, {});
        }

        if (phase == Phase::YassyStory1) {
            texturesP->DrawTexts("Press ENTER", white, black, { 960,120,1,1 }, 0, Anchor::Center);
        }

    }

    if (phase == Phase::YassyStory1) {
        if (inputP->event.RETURN) {
            phase = Phase::YassyStory2;
        }
    }

    if (phase == Phase::YassyStory2) {
        BTNstart.visible = true;
        BTNoptions.visible = true;
        BTNcredits.visible = true;
        BTNexitgame.visible = true;

        BTNstart.state = State::Idle;
        BTNoptions.state = State::Idle;
        BTNcredits.state = State::Idle;
        BTNexitgame.state = State::Idle;
    }
    else {
        BTNstart.visible = false;
        BTNoptions.visible = false;
        BTNcredits.visible = false;
        BTNexitgame.visible = false;
    }

    if (phase == Phase::Options) {
        options.Update();
        options.Show();
    }
    else {
        options.Hide();
    }
    
    if (phase == Phase::Credits) {
        OBJRECT fullScreen = { settings::baseW / 2, settings::baseH / 2, settings::baseW,settings::baseH, 1 };
        texturesP->DrawImage("assy", fullScreen, 0, {});
        texturesP->DrawRect({255,255,255,200}, fullScreen, 0);

        uiCredits.Update();
        BTNface.state = State::Idle;
        BTNback.state = State::Idle;

        SDL_Color c1 = { 255,255,255,255 };
        SDL_Color c2 = { 0,0,0,255 };
        texturesP->DrawTexts("==Programming==", c1, c2, { 500,1000,1.5,1.5 }, 0, Anchor::Center);
        texturesP->DrawTexts("Chikuwaaan", c1, c2, { 500,900,1,1 }, 0, Anchor::Center);

        texturesP->DrawTexts("==Graphics==", c1, c2, { 500,700,1.5,1.5 }, 0, Anchor::Center);
        texturesP->DrawTexts("Chikuwaaan", c1, c2, { 500,600,1,1 }, 0, Anchor::Center);
        texturesP->DrawTexts("Yassy1008", c1, c2, { 500,500,1,1 }, 0, Anchor::Center);
        texturesP->DrawTexts("Sasaki_Family", c1, c2, { 500,400,1,1 }, 0, Anchor::Center);

        texturesP->DrawTexts("==Sounds==", c1, c2, { 1420,1000,1.5,1.5 }, 0, Anchor::Center);
        texturesP->DrawTexts("Chikuwaaan", c1, c2, { 1420,900,1,1 }, 0, Anchor::Center);
        texturesP->DrawTexts(u8"効果音ラボ", c1, c2, { 1420,800,1,1 }, 0, Anchor::Center);

        texturesP->DrawTexts("==Playtester==", c1, c2, { 1420,700,1.5,1.5 }, 0, Anchor::Center);
        texturesP->DrawTexts("youmeay", c1, c2, { 1420,600,1,1 }, 0, Anchor::Center);

        texturesP->DrawTexts("==Special Thanks==", c1, c2, { 960,200,1.5,1.5 }, 0, Anchor::Center);
        texturesP->DrawTexts("Yassy and everyone!!!", c1, c2, { 960,100,1,1 }, 0, Anchor::Center);

        if (inputP->GetEvent(Event::Back)) {
            BTNback.action;
        }
    }

    ui.Update();
}