#include "Options.h"
#include "UIManager.h"
#include "Sounds.h"
#include "Textures.h"
#include "namespace.h"
#include "Input.h"

Sounds* Options::soundsP = nullptr;
Textures* Options::texturesP = nullptr;
Input* Options::inputP = nullptr;

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
    Up(800, settings::baseH / 2 + 200, 96, 96),
    Down(800, settings::baseH / 2 + 100, 96, 96),
    Left(800, settings::baseH / 2 + 000, 96, 96),
    Right(800, settings::baseH / 2 - 100, 96, 96),
    Jump(1460, settings::baseH / 2 + 200, 96, 96),
    Dash(1460, settings::baseH / 2 + 100, 96, 96),
    Confirm(1460, settings::baseH / 2 + 000, 96, 96),
    Back(1460, settings::baseH / 2 - 100, 96, 96),
    Invert(800, settings::baseH / 2 - 200, 96, 96),
    Blur(800, settings::baseH / 2 - 300, 96, 96),
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
    CONFIGS1.push_back(&Up);
    CONFIGS1.push_back(&Down);
    CONFIGS1.push_back(&Left);
    CONFIGS1.push_back(&Right);
    CONFIGS2.push_back(&Jump);
    CONFIGS2.push_back(&Dash);
    CONFIGS2.push_back(&Confirm);
    CONFIGS2.push_back(&Back);
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

    Up.action = []() {
        inputP->SetConfig(Action::HoldUp);
        };
    Down.action = []() {
        inputP->SetConfig(Action::HoldDown);
        };
    Left.action = []() {
        inputP->SetConfig(Action::HoldLeft);
        };
    Right.action = []() {
        inputP->SetConfig(Action::HoldRight);
    };
    Jump.action = []() {
        inputP->SetConfig(Action::HoldJump);
        };
    Dash.action = []() {
        inputP->SetConfig(Action::HoldRun);
        };
    Confirm.action = []() {
        inputP->SetEventConfig(Event::Confirm);
        };
    Back.action = []() {
        inputP->SetEventConfig(Event::Back);
        };
    Invert.action = []() {
        if (savedata::InvertDash) {
            savedata::InvertDash = 0;
        }
        else {
            savedata::InvertDash = 1;
        }
        };
    Blur.action = []() {
        if (savedata::Blur) {
            savedata::Blur = 0;
        }
        else {
            savedata::Blur = 1;
        }
        };

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
        &config1,
        [this]() {
            this->ui.currentButton = settings::SE / 16;
        },
        [](){}
    };
    config1 = {
        CONFIGS1,
        DIRECTION::V,
        nullptr,
        &config2,
        []() {},
        []() {},
        [this]() {
            this->ui.currentLine = &lineBGM;
            this->ui.currentButton = settings::BGM / 16;
        },
        [this]() {
            this->ui.currentLine = &sita;
            this->ui.currentButton = 0;
        }
    };
    config2 = {
        CONFIGS2,
        DIRECTION::V,
        &config1,
        nullptr,
        []() {},
        []() {},
        [this]() {
            this->ui.currentLine = &lineBGM;
            this->ui.currentButton = settings::BGM / 16;
        },
        [this]() {
            this->ui.currentLine = &sita;
            this->ui.currentButton = 0;
        }
    };
    sita = {
        {&Invert, &Blur},
        DIRECTION::V,
        nullptr,
        nullptr,
        [](){},
        []() {},
        [this]() {
            this->ui.currentLine = &config1;
            this->ui.currentButton = 3;
        },
        [this]() {
            this->ui.currentLine = &back;
            this->ui.currentButton = 0;
        }
    };
    back = {
        {&BTNback},
        DIRECTION::H,
        &sita,
        nullptr,
        [this]() {
            this->ui.currentButton = 1;
        }
    };

    ui.AddLine(&lineSE);
    ui.AddLine(&lineBGM);
    ui.AddLine(&config1);
    ui.AddLine(&config2);
    ui.AddLine(&sita);
    ui.AddLine(&back);
    ui.currentLine = &lineSE;
}

void Options::Show() {
    int i = 0;
    for (auto& p : SE) {
        p->x = i * 112 + 800;
        p->y = settings::baseH / 2 + 400;
        p->w = 96;
        p->h = 96;
        p->icon = static_cast<Icons>(i + 11);
        p->visible = true;
        i++;
    }
    i = 0;
    for (auto& p : BGM) {
        p->x = i * 112 + 800;
        p->y = settings::baseH / 2 + 300;
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
    OBJRECT rect = { settings::baseW / 2.0, settings::baseH / 2.0, 1600,1000 , 1};
    SDL_Color white = { 255,255,255,255 };
    SDL_Color black = { 0,0,0,255 };
    texturesP->DrawRect({ 255,255,140,127 }, rect, 0);

    double SEy = settings::baseH / 2 + 400;
    double BGMy = settings::baseH / 2 + 300;
    double Upy = settings::baseH / 2 + 200;
    double Downy = settings::baseH / 2 + 100;
    double Lefty = settings::baseH / 2 + 0;
    double Righty = settings::baseH / 2 - 100;
    double Jumpy = settings::baseH / 2 + 200;
    double Dashy = settings::baseH / 2 + 100;
    double Confirmy = settings::baseH / 2 + 00;
    double Backy = settings::baseH / 2 - 100;
    double Inverty = settings::baseH / 2 - 200;
    double Blury = settings::baseH / 2 - 300;
    texturesP->DrawTexts("SE volume:", white, black, { 300, SEy, 1, 1 }, 0, Anchor::Left);
    texturesP->DrawTexts("BGM volume:", white, black, { 300, BGMy, 1, 1 }, 0, Anchor::Left);
    texturesP->DrawTexts("Up key:", white, black, { 300, Upy, 1, 1 }, 0, Anchor::Left);
    texturesP->DrawTexts("Down key", white, black, { 300, Downy, 1, 1 }, 0, Anchor::Left);
    texturesP->DrawTexts("Left key:", white, black, { 300, Lefty, 1, 1 }, 0, Anchor::Left);
    texturesP->DrawTexts("Right key:", white, black, { 300, Righty, 1, 1 }, 0, Anchor::Left);
    texturesP->DrawTexts("Jump key:", white, black, { 960, Jumpy, 1, 1 }, 0, Anchor::Left);
    texturesP->DrawTexts("Dash key:", white, black, { 960, Dashy, 1, 1 }, 0, Anchor::Left);
    texturesP->DrawTexts("Confirm key:", white, black, { 960, Confirmy, 1, 1 }, 0, Anchor::Left);
    texturesP->DrawTexts("Back key:", white, black, { 960, Backy, 1, 1 }, 0, Anchor::Left);
    texturesP->DrawTexts("Invert Dash:", white, black, { 300, Inverty, 1, 1 }, 0, Anchor::Left);
    texturesP->DrawTexts("Blur:", white, black, { 300, Blury, 1, 1 }, 0, Anchor::Left);

    Up.text = inputP->GetConfigName(Action::HoldUp);
    Down.text = inputP->GetConfigName(Action::HoldDown);
    Left.text = inputP->GetConfigName(Action::HoldLeft);
    Right.text = inputP->GetConfigName(Action::HoldRight);
    Jump.text = inputP->GetConfigName(Action::HoldJump);
    Dash.text = inputP->GetConfigName(Action::HoldRun);
    Confirm.text = inputP->GetEventConfigName(Event::Confirm);
    Back.text = inputP->GetEventConfigName(Event::Back);

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
    for (auto& p : CONFIGS1) {
        p->state = State::Idle;
    }
    for (auto& p : CONFIGS2) {
        p->state = State::Idle;
    }

    Invert.state = State::Idle;
    if (savedata::InvertDash) {
        Invert.icon = Icons::On;
    }
    else {
        Invert.icon = Icons::Off;
    }
    Blur.state = State::Idle;
    if (savedata::Blur) {
        Blur.icon = Icons::On;
    }
    else {
        Blur.icon = Icons::Off;
    }

    BTNback.state = State::Idle;


    ui.Update();
    if (inputP->setting != Action::Null || inputP->eventSetting != Event::Null) {
        texturesP->DrawImage("ose", {960,540,1920,1080}, 0, {});
    }
}