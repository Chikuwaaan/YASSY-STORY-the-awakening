#include "OverLay.h"
#include "namespace.h"
#include "Textures.h"

Textures* OverLay::texturesP = nullptr;

OverLay::OverLay() {
    pinHole = { 0,0,0,0,{0,0,0,0} };
    fade = { 0,0,0,{0,0,0,0} };
    //PinHole(1000, 100, { 0,0,0,255 });
}

/*
void OverLay::Update() {
    SDL_Renderer* r = settings::renderer;
    if (pinHole.effect) {
        SDL_Texture* texture = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, settings::baseW, settings::baseH);
        SDL_SetRenderTarget(r, texture);

        SDL_Rect rect = { 0, 0, settings::baseW, settings::baseH };
        SDL_SetRenderDrawColor(r, pinHole.color.r, pinHole.color.g, pinHole.color.b, pinHole.color.a);
        SDL_RenderFillRect(r, &rect);

        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_MOD);
        OBJRECT pRect = playerP->GetRect();
        OBJRECT dst;
        dst.x = (int)pRect.x;
        dst.y = (int)pRect.y;
        dst.w = pinHole.radius * 2;
        dst.h = pinHole.radius * 2;
        pinHole.radius -= pinHole.shrinkSpeed * settings::timeScale;
        if (pinHole.radius <= 0) {
            pinHole.radius = 0;
            pinHole.waitTime -= settings::timeScale;
            if (pinHole.waitTime < 0) {
                pinHole.effect = 0;
            }
        }
        texturesP->DrawImage("circle_mask", dst, 1, {});

        SDL_SetRenderTarget(r, nullptr);
        SDL_RenderCopy(r, texture, NULL, &rect);
        SDL_DestroyTexture(texture);
    }

    if (fade.effect) {
        SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
        OBJRECT rect = { (double)settings::baseW/2.0, (double)settings::baseH/2.0, (double)settings::baseW, (double)settings::baseH, 1 };
        fade.time -= settings::timeScale;
        if (fade.time < 0) {
            fade.effect = 0;
            return;
        }

        if (fade.effect == 1) {
            fade.color.a = (int)(255 * (fade.time / fade.speed));
        }
        else if (fade.effect == -1) {
            fade.color.a = (int)(255 - 255 * (fade.time / fade.speed));
        }

        if (fade.color.a > 255) fade.color.a = 255;
        if (fade.color.a < 0) fade.color.a = 0;
        
        texturesP->DrawRect(fade.color, rect, 0);

        
        
    }

    //OBJRECT rect = { 0, 0, (double)settings::baseW, (double)settings::baseH };
    //texturesP->DrawRect({ 0,0,0,255 }, rect, 0);
}

void OverLay::PinHole(double radius, double shrinkSpeed, double waitTime, SDL_Color color) {
    pinHole.effect = 1;
    pinHole.radius = radius;
    pinHole.shrinkSpeed = shrinkSpeed;
    pinHole.waitTime = waitTime;
    pinHole.color = color;
}

void OverLay::FadeOut(double speed, SDL_Color color) {
    fade.effect = -1;
    fade.speed = speed;
    fade.time = speed;
    fade.color = color;
}

void OverLay::FadeIn(double speed, SDL_Color color) {
    fade.effect = 1;
    fade.speed = speed;
    fade.time = speed;
    fade.color = color;
}
*/

void OverLay::Update() {};
void OverLay::PinHole(double radius, double shrinkSpeed, double waitTime, SDL_Color color) {};
void OverLay::FadeOut(double speed, SDL_Color color) {};
void OverLay::FadeIn(double speed, SDL_Color color) {};