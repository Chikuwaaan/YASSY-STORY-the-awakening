#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <map>
#include <filesystem>

class Sounds
{
public:
    Sounds();
    std::map<std::string, Mix_Chunk*> map;
    void LoadSounds(std::filesystem::path directoryPath);
    void SetSEVolume(int value);
    void SetBGMVolume(int value);
    void PlaySE(std::string name);
};

