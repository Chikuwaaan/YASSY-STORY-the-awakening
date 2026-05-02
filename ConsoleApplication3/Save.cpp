#include "Save.h"
#include <fstream>
#include <string>
#include "namespace.h"
#include "Input.h"
#include "Sounds.h"
#include <iostream>

Input* Save::inputP = nullptr;
Sounds* Save::soundsP = nullptr;

Save::Save() {

}

void Save::LoadOptions() {
    std::ifstream option("Save/option.txt");
    if (option.is_open()) {
        int format;
        option >> format;

        if (format == 1) {
            option >> settings::BGM;
            option >> settings::SE;
            soundsP->SetBGMVolume(settings::BGM);
            soundsP->SetSEVolume(settings::SE);

            int device, code;
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
    }
    option.close();

    /*
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
    */
}

void Save::WriteOptions() {
    std::ofstream option("Save/option.txt");
    if (option.is_open()) {
        option << 1 << std::endl;
        option << settings::BGM << std::endl;
        option << settings::SE << std::endl;
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

    /*
    std::ofstream progress("Save/progress.bin", std::ios::binary);
    int version = 1;

    progress.write((char*)&version, sizeof(int));

    for (int i = 0; i < savedata::coin.size(); i++) {
        for (int j = 0; j < 3; j++) {
            int coin = savedata::coin[i][j];
            progress.write((char*)&coin, sizeof(int));
        }
    }
    */
}


/* current
* format version
* 今のレベル
* 今のcp
* coin0
* coin1
* coin2
*/

void Save::LoadProgress(int slot) {
    LoadCurrent(slot);
    LoadProg(slot);
}

void Save::LoadCurrent(int slot) {
    std::string path = "Save/";
    path = path + std::to_string(slot) + "/current.bin";
    std::ifstream current(path);
    if (!current.is_open()) {
        platformer::CP = 0;
        platformer::coin[0] = 0;
        platformer::coin[1] = 0;
        platformer::coin[2] = 0;
        return;
    }

    int format;
    current.read((char*)&format, sizeof(int));

    if (format == 1) {
        int a;
        current.read((char*)&a, sizeof(int));
        if (a != 0) platformer::level = a;
        current.read((char*)&platformer::CP, sizeof(int));
        current.read((char*)&platformer::coin[0], sizeof(int));
        current.read((char*)&platformer::coin[1], sizeof(int));
        current.read((char*)&platformer::coin[2], sizeof(int));
    }
    current.close();
}

void Save::LoadProg(int slot) {
    std::string path = "Save/";
    path = path + std::to_string(slot) + "/progress.bin";
    std::ifstream file(path);
    if (!file.is_open()) {
        for (int i = 0; i < 10; i++) {
            savedata::completedLevel[i] = 0;
            savedata::coin[i] = { 0,0,0 };
        }
        return;
    }

    int format;
    file.read((char*)&format, sizeof(int));

    if (format == 1) {
        for (int i = 0; i < 10; i++) {
            file.read((char*)&savedata::completedLevel[i], sizeof(int));

            for (int j = 0; j < 3; j++) {
                file.read((char*)&savedata::coin[i][j], sizeof(int));
            }
        }
    }
    file.close();
}

void Save::WriteProgress(int slot) {
    std::filesystem::create_directories("Save/1");
    std::filesystem::create_directories("Save/2");
    std::filesystem::create_directories("Save/3");

    WriteCurrent(slot);
    WriteProg(slot);
}

void Save::WriteCurrent(int slot) {
    std::string path = "Save/";
    path = path + std::to_string(slot) + "/current.bin";
    std::ofstream current(path, std::ios::binary);

    int format = 1;
    current.write((char*)&format, sizeof(int));
    int currentLevel = platformer::level;
    current.write((char*)&currentLevel, sizeof(int));
    int currentCP = platformer::CP;
    current.write((char*)&currentCP, sizeof(int));

    current.write((char*)&(platformer::coin[0]), sizeof(int));
    current.write((char*)&(platformer::coin[1]), sizeof(int));
    current.write((char*)&(platformer::coin[2]), sizeof(int));

    current.close();
}

void Save::WriteProg(int slot) {
    std::string path = "Save/";
    path = path + std::to_string(slot) + "/progress.bin";
    std::ofstream progress(path, std::ios::binary);

    int format = 1;
    progress.write((char*)&format, sizeof(int));

    for (int i = 0; i < 10; i++) {
        int completed = savedata::completedLevel[i];
        progress.write((char*)&completed, sizeof(int));

        for (int j = 0; j < 3; j++) {
            int coin = savedata::coin[i][j];
            progress.write((char*)&coin, sizeof(int));
        }
    }

    progress.close();
}