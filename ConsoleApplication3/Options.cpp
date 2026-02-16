#include "Options.h"
#include "UIManager.h"
#include "Sounds.h"
#include "Textures.h"

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
    BGM8(0, 0, 0, 0),
    BTNback(100,100,192,192)
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
        p->action = [i]() {
            soundsP->SetSEVolume(i * 16);
            };
        i++;
    }
    i = 0;
    for (auto& p : BGM) {
        p->action = [i]() {
            soundsP->SetBGMVolume(i * 16);
            };
        i++;
    }

    lineSE = {
        SE,
        DIRECTION::H,
        nullptr,
        &lineBGM,
        []() {},
        [this]() {
            this->ui.currentButton = settings::BGM / 16;
        }
    };
    lineBGM = {
        BGM,
        DIRECTION::H,
        &lineSE,
        &back,
        [this]() {
            this->ui.currentButton = settings::SE / 16;
        },
        [](){}
    };
    back = {
        {&BTNback},
        DIRECTION::H,
        &lineBGM,
        nullptr,
        [this]() {
            this->ui.currentButton = settings::BGM / 16;
        }
    };

    ui.AddLine(&lineSE);
    ui.AddLine(&lineBGM);
    ui.AddLine(&back);
    ui.currentLine = &lineSE;
}

void Options::Show() {
    int i = 0;
    for (auto& p : SE) {
        p->x = i * 112 + 800;
        p->y = settings::baseH / 2 + 200;
        p->w = 96;
        p->h = 96;
        p->icon = static_cast<Icons>(i + 11);
        p->visible = true;
        i++;
    }
    i = 0;
    for (auto& p : BGM) {
        p->x = i * 112 + 800;
        p->y = settings::baseH / 2 - 200;
        p->w = 96;
        p->h = 96;
        p->icon = static_cast<Icons>(i + 11);
        p->visible = true;
        i++;
    }
}

void Options::Hide() {
    for (auto& p : SE) {
        p->visible = false;
    }
    for (auto& p : BGM) {
        p->visible = false;
    }
}

void Options::Update() {
    OBJRECT rect = { settings::baseW / 2.0, settings::baseH / 2.0, 1600,800 , 1};
    SDL_Color white = { 255,255,255,255 };
    SDL_Color black = { 0,0,0,255 };
    texturesP->DrawRect({ 255,255,140,255 }, rect, 0);

    double SEy = settings::baseH / 2 + 200;
    double BGMy = settings::baseH / 2 - 200;
    texturesP->DrawTexts("SE volume:", white, black, { 300, SEy, 1, 1 }, 0, Anchor::Left);
    texturesP->DrawTexts("BGM volume:", white, black, { 300, BGMy, 1, 1 }, 0, Anchor::Left);

    int i = 0;
    for (auto& p : SE) {
        if (settings::SE / 16.0 == i) {
            p->state = State::Unavailable;
        }
        else {
            p->state = State::Idle;
        }
        i++;
    }
    i = 0;
    for (auto& p : BGM) {
        if (settings::BGM / 16.0 == i) {
            p->state = State::Unavailable;
        }
        else {
            p->state = State::Idle;
        }
        i++;
    }
    BTNback.state = State::Idle;
    ui.Update();
}