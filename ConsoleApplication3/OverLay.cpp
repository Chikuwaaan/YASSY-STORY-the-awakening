#include "OverLay.h"
#include "namespace.h"
#include "Textures.h"

Textures* OverLay::texturesP = nullptr;

OverLay::OverLay() {
    pinHole = { 0,0,0,{0,0,0,0} };
}

void OverLay::Update() {
    SDL_Renderer* r = settings::renderer;
    SDL_Texture* texture = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, settings::baseW, settings::baseH);
    SDL_SetRenderTarget(r, texture);

    SDL_Rect rect = { 0, 0, settings::baseW, settings::baseH };
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderFillRect(r, &rect);
    //SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_MUL);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_MOD);
    SDL_RenderCopy(r, texturesP->map["circle_mask"], NULL, NULL);

    SDL_SetRenderTarget(r, nullptr);
    SDL_RenderCopy(r, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    
}

void OverLay::PinHole() {

}