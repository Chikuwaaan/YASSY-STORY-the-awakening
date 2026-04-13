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
    std::ifstream file("Save/savedata.txt");

    int device, code;
    if (file.is_open()) {
        for (int i = 1; i <= 6; i++) {
            file >> device;
            file >> code;
            inputP->config[(Action)i].device = (InputDevice)device;
            inputP->config[(Action)i].code = code;
        }
    }

    file.close();
    std::cout << "[DEBUG]loaded!" << std::endl;
}

void Save::Write() {
    std::ofstream file("Save/savedata.txt");

    if (file.is_open()) {
        file << (int)inputP->config[Action::HoldUp].device << std::endl;
        file << (int)inputP->config[Action::HoldUp].code << std::endl;
        file << (int)inputP->config[Action::HoldDown].device << std::endl;
        file << (int)inputP->config[Action::HoldDown].code << std::endl;
        file << (int)inputP->config[Action::HoldLeft].device << std::endl;
        file << (int)inputP->config[Action::HoldLeft].code << std::endl;
        file << (int)inputP->config[Action::HoldRight].device << std::endl;
        file << (int)inputP->config[Action::HoldRight].code << std::endl;
        file << (int)inputP->config[Action::HoldJump].device << std::endl;
        file << (int)inputP->config[Action::HoldJump].code << std::endl;
        file << (int)inputP->config[Action::HoldRun].device << std::endl;
        file << (int)inputP->config[Action::HoldRun].code << std::endl;
    }

    file.close();
    std::cout << "[DEBUG]saved!" << std::endl;
}