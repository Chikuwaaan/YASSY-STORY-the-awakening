#include "Zako.h"
#include "SDL_mixer.h"

Zako::Zako() {
    type = entityType::Zako;
    x = 1100;
    y = 300;
}

void Zako::Update() {

}

void Zako::Damage() {
    dead = 1;
    Mix_Chunk* se = Mix_LoadWAV("Assets/sounds/1kill.wav");
    Mix_PlayChannel(-1, se, 0);
}