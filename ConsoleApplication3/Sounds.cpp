#include "Sounds.h"
#include <iostream>
#include "namespace.h"

namespace fs = std::filesystem;

Sounds::Sounds() {
    currentMusic = nullptr;
    LoadSounds("Assets/sounds/SE");
    LoadMusics("Assets/sounds/MUSIC");
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

                if (SE.count(key) == 0) {
                    SE[key] = Mix_LoadWAV(c);
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

void Sounds::LoadMusics(std::filesystem::path directoryPath) {
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            std::string ext = entry.path().extension().string();

            if (ext == ".ogg" || ext == ".wav" || ext == ".mp3") {
                std::string filePath = entry.path().string();
                std::string key = entry.path().stem().string();
                const char* c = filePath.c_str();

                if (MUSIC.count(key) == 0) {
                    MUSIC[key] = Mix_LoadMUS(c);
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
    Mix_PlayChannel(-1, SE[name], 0);
}

void Sounds::PlayMusic(std::string name) {
    currentMusic = MUSIC[name];
    Mix_PlayMusic(currentMusic, -1);
}

double Sounds::GetMusicPosition() {
    if (currentMusic) {
        return Mix_GetMusicPosition(currentMusic);
    }
    else {
        return 0;
    }
}