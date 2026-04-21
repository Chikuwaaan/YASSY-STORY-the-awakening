#include "Save.h"
#include <fstream>
#include <string>
#include "namespace.h"
#include "Input.h"
#include <iostream>

Input* Save::inputP = nullptr;

Save::Save() {

}

void Save::Load() {
    std::ifstream option("Save/option.txt");
    int device, code;
    if (option.is_open()) {
        for (int i = 1; i <= 6; i++) {
            option >> device;
            option >> code;
            inputP->config[(Action)i].device = (InputDevice)device;
            inputP->config[(Action)i].code = code;
        }
        for (int i = 1; i <= 2; i++) {
            option >> device;
            option >> code;
            inputP->eventConfig[(Event)i].device = (InputDevice)device;
            inputP->eventConfig[(Event)i].code = code;
        }
        option >> savedata::InvertDash;
        option >> savedata::Blur;
    }
    option.close();

    std::ifstream progress("Save/progress.bin");
    if (progress.is_open()) {
        int version = 0;
        progress.read((char*)&version, sizeof(version));

        if (version == 1) {
            for (int i = 0; i < savedata::coin.size(); i++) {
                for (int j = 0; j < 3; j++) {
                    progress.read((char*)&(savedata::coin[i][j]), sizeof(int));
                }
            }
        }
    }
    


    std::cout << "[DEBUG]loaded!" << std::endl;
}

void Save::Write() {
    std::ofstream option("Save/option.txt");
    if (option.is_open()) {
        option << (int)inputP->config[Action::HoldUp].device << std::endl;
        option << (int)inputP->config[Action::HoldUp].code << std::endl;
        option << (int)inputP->config[Action::HoldDown].device << std::endl;
        option << (int)inputP->config[Action::HoldDown].code << std::endl;
        option << (int)inputP->config[Action::HoldLeft].device << std::endl;
        option << (int)inputP->config[Action::HoldLeft].code << std::endl;
        option << (int)inputP->config[Action::HoldRight].device << std::endl;
        option << (int)inputP->config[Action::HoldRight].code << std::endl;
        option << (int)inputP->config[Action::HoldJump].device << std::endl;
        option << (int)inputP->config[Action::HoldJump].code << std::endl;
        option << (int)inputP->config[Action::HoldRun].device << std::endl;
        option << (int)inputP->config[Action::HoldRun].code << std::endl;
        option << (int)inputP->eventConfig[Event::Confirm].device << std::endl;
        option << (int)inputP->eventConfig[Event::Confirm].code << std::endl;
        option << (int)inputP->eventConfig[Event::Back].device << std::endl;
        option << (int)inputP->eventConfig[Event::Back].code << std::endl;
        option << savedata::InvertDash << std::endl;
        option << savedata::Blur << std::endl;
    }
    option.close();

    std::ofstream progress("Save/progress.bin", std::ios::binary);
    int version = 1;

    progress.write((char*)&version, sizeof(int));

    for (int i = 0; i < savedata::coin.size(); i++) {
        for (int j = 0; j < 3; j++) {
            int coin = savedata::coin[i][j];
            progress.write((char*)&coin, sizeof(int));
        }
    }

    std::cout << "[DEBUG]saved!" << std::endl;
}