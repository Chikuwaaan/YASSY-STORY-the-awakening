#include "Zako.h"
#include "SDL_mixer.h"
#include "Player.h"

Zako::Zako(double x0, double y0) {
    texName = "nsfw";
    type = EntityType::Zako;
    x = x0;
    y = y0;
    w = 80;
    h = 80;
}

void Zako::Update() {

}

void Zako::Touched() {
    playerP->Die();
}

void Zako::Stomped() {
    dead = 1;
    Mix_Chunk* se = Mix_LoadWAV("Assets/sounds/1kill.wav");
    Mix_PlayChannel(-1, se, 0);
}