#include "Zako.h"
#include "SDL_mixer.h"

Zako::Zako(double x0, double y0) {
    texName = "missing";
    type = entityType::Zako;
    x = x0;
    y = y0;
    w = 80;
    h = 80;
}

void Zako::Update() {

}

void Zako::Damage() {
    dead = 1;
    Mix_Chunk* se = Mix_LoadWAV("Assets/sounds/1kill.wav");
    Mix_PlayChannel(-1, se, 0);
}