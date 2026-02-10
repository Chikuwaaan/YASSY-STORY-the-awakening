#include "Sounds.h"
#include <iostream>
#include "namespace.h"

namespace fs = std::filesystem;

Sounds::Sounds() {
    LoadSounds("Assets/sounds");
    SetSEVolume(settings::SE);
    SetBGMVolume(settings::BGM);
}

void Sounds::SetSEVolume(int value) {
    settings::SE = value;
    Mix_MasterVolume(settings::SE);
}

void Sounds::SetBGMVolume(int value) {
    settings::BGM = value;
    Mix_VolumeMusic(settings::BGM);
}

void Sounds::LoadSounds(std::filesystem::path directoryPath) {
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            std::string ext = entry.path().extension().string();

            if (ext == ".ogg" || ext == ".wav" || ext == ".mp3") {
                std::string filePath = entry.path().string();
                std::string key = entry.path().stem().string();
                const char* c = filePath.c_str();

                if (map.count(key) == 0) {
                    map[key] = Mix_LoadWAV(c);
                    std::cout << "[DEBUG]音声を読み込みました" << std::endl;
                }
                else {
                    std::cout << "[DEBUG]音声の読み込みに失敗しました：ファイル名が重複しています" << filePath << std::endl;
                }
            }

        }
        else if (entry.is_directory()) {
            LoadSounds(entry.path());
        }
    }
}

void Sounds::PlaySE(std::string name) {
    Mix_PlayChannel(-1, map[name], 0);
}