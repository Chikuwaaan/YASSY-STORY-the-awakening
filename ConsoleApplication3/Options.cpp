#include "Options.h"
#include "UIManager.h"
#include "Sounds.h"
#include "Textures.h"

UIManager* Options::uiP = nullptr;
Sounds* Options::soundsP = nullptr;
Textures* Options::texturesP = nullptr;

Options::Options() :
    SE0(0, 0, 0, 0),
    SE1(0, 0, 0, 0),
    SE2(0, 0, 0, 0),
    SE3(0, 0, 0, 0),
    SE4(0, 0, 0, 0),
    SE5(0, 0, 0, 0),
    SE6(0, 0, 0, 0),
    SE7(0, 0, 0, 0),
    SE8(0, 0, 0, 0),
    BGM0(0, 0, 0, 0),
    BGM1(0, 0, 0, 0),
    BGM2(0, 0, 0, 0),
    BGM3(0, 0, 0, 0),
    BGM4(0, 0, 0, 0),
    BGM5(0, 0, 0, 0),
    BGM6(0, 0, 0, 0),
    BGM7(0, 0, 0, 0),
    BGM8(0, 0, 0, 0)
{
    SE.push_back(&SE0);
    SE.push_back(&SE1);
    SE.push_back(&SE2);
    SE.push_back(&SE3);
    SE.push_back(&SE4);
    SE.push_back(&SE5);
    SE.push_back(&SE6);
    SE.push_back(&SE7);
    SE.push_back(&SE8);
    BGM.push_back(&BGM0);
    BGM.push_back(&BGM1);
    BGM.push_back(&BGM2);
    BGM.push_back(&BGM3);
    BGM.push_back(&BGM4);
    BGM.push_back(&BGM5);
    BGM.push_back(&BGM6);
    BGM.push_back(&BGM7);
    BGM.push_back(&BGM8);
}

void Options::RegisterButtons() {
    int i = 0;
    for (auto& p : SE) {
        uiP->AddButton(p);
        p->action = [i]() {
            soundsP->SetSEVolume(i * 16);
            };
        i++;
    }
    i = 0;
    for (auto& p : BGM) {
        uiP->AddButton(p);
        p->action = [i]() {
            soundsP->SetBGMVolume(i * 16);
            };
        i++;
    }
}

void Options::Show() {
}

void Options::Hide() {
    for (auto& p : SE) {
        p->state = State::Invisible;
    }
    for (auto& p : BGM) {
        p->state = State::Invisible;
    }
}

void Options::Update() {
    OBJRECT rect = { settings::baseW / 2.0, settings::baseH / 2.0, 1600,800 , 1};
    SDL_Color white = { 255,255,255,255 };
    SDL_Color black = { 0,0,0,255 };
    texturesP->DrawRect({ 117,226,255,255 }, rect, 0);

    double SEy = settings::baseH / 2 + 200;
    double BGMy = settings::baseH / 2 - 200;
    texturesP->DrawTexts("SE volume:", white, black, { 300, SEy, 1, 1 }, 0, Anchor::Left);
    texturesP->DrawTexts("BGM volume:", white, black, { 300, BGMy, 1, 1 }, 0, Anchor::Left);

    int i = 0;
    for (auto& p : SE) {
        p->x = i * 96 + 800;
        p->y = settings::baseH / 2 + 200;
        p->w = 64;
        p->h = 64;
        p->icon = static_cast<Icons>(i+11);
        p->state = State::Available;
        i++;
    }
    i = 0;
    for (auto& p : BGM) {
        p->x = i * 96 + 800;
        p->y = settings::baseH / 2 - 200;
        p->w = 64;
        p->h = 64;
        p->state = State::Available;
        i++;
    }
}