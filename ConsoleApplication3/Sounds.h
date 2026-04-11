#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <map>
#include <filesystem>

class Sounds
{
private:
    Mix_Music* currentMusic;
public:
    Sounds();
    std::map<std::string, Mix_Chunk*> SE;
    std::map<std::string, Mix_Music*> MUSIC;
    void LoadSounds(std::filesystem::path directoryPath);
    void LoadMusics(std::filesystem::path directoryPath);
    void SetSEVolume(int value);
    void SetBGMVolume(int value);
    void PlaySE(std::string name);
    void PlayMusic(std::string name);
    double GetMusicPosition();
};

