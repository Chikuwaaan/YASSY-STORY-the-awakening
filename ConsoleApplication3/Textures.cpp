#include "Textures.h"
#include "namespace.h"
#include "Camera.h"

Camera* Textures::cameraP = nullptr;

Textures::Textures() {
    LoadTextures();
    font = TTF_OpenFont("C:/Windows/Fonts/meiryo.ttc", 50);
}

void Textures::LoadTextures() {
    for (auto [_, value] : map) {
        SDL_DestroyTexture(value);
    }
    map["missing"] = IMG_LoadTexture(settings::renderer, "Assets/textures/missing.png");
    map["1"] = IMG_LoadTexture(settings::renderer, "Assets/textures/BAN.png");
    map["2"] = IMG_LoadTexture(settings::renderer, "Assets/textures/dokufee.png");
    map["3"] = IMG_LoadTexture(settings::renderer, "Assets/textures/assy2.png");
    map["4"] = IMG_LoadTexture(settings::renderer, "Assets/textures/dotchiku.png");
    map["5"] = IMG_LoadTexture(settings::renderer, "Assets/textures/nsfw.png");
    map["assy"] = IMG_LoadTexture(settings::renderer, "Assets/textures/assy.png");
    map["assy2"] = IMG_LoadTexture(settings::renderer, "Assets/textures/assy2.png");
    map["assyChara"] = IMG_LoadTexture(settings::renderer, "Assets/textures/assyChara.png");
    map["legL"] = IMG_LoadTexture(settings::renderer, "Assets/textures/legL.png");
    map["legR"] = IMG_LoadTexture(settings::renderer, "Assets/textures/legR.png");
    map["body"] = IMG_LoadTexture(settings::renderer, "Assets/textures/body.png");
    map["head"] = IMG_LoadTexture(settings::renderer, "Assets/textures/head.png");
    map["armL"] = IMG_LoadTexture(settings::renderer, "Assets/textures/armL.png");
    map["armR"] = IMG_LoadTexture(settings::renderer, "Assets/textures/armR.png");
    map["unko"] = IMG_LoadTexture(settings::renderer, "Assets/textures/unko.png");
    map["camera"] = IMG_LoadTexture(settings::renderer, "Assets/textures/camera.png");
    std::cout << "[DEBUG]テクスチャをロードしました" << std::endl;
}

void Textures::DrawImage(std::string texName, OBJRECT rect) {
    CAMERA camera = cameraP->GetCam();
    double pivotX = settings::baseW / 2.0;
    double pivotY = settings::baseH / 2.0;
    SDL_Rect dst;
    //ちょっとよくわからん
    dst.x = (int)((rect.x - rect.w * 0.5 - (camera.x - pivotX + camera.offsetX + settings::baseW * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
    dst.y = (int)(settings::baseH - ((rect.y + rect.h * 0.5) - (camera.y - pivotY + camera.offsetY + settings::baseH * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
    dst.w = (int)(rect.w * camera.zoom);
    dst.h = (int)(rect.h * camera.zoom);
    SDL_Rect ds = { 200,200,200,200 };
    SDL_RenderCopy(settings::renderer, GetTexture(texName), NULL, &dst);
}

void Textures::DrawImageEx(std::string texName, OBJRECT rect, double angle, OBJRECT center, bool flipX, bool flipY) {
    CAMERA camera = cameraP->GetCam();
    double pivotX = settings::baseW / 2.0;
    double pivotY = settings::baseH / 2.0;
    SDL_Rect dst;
    dst.x = (int)((rect.x - rect.w * 0.5 - (camera.x - pivotX + camera.offsetX + settings::baseW * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
    dst.y = (int)(settings::baseH - ((rect.y + rect.h * 0.5) - (camera.y - pivotY + camera.offsetY + settings::baseH * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
    dst.w = (int)(rect.w * camera.zoom);
    dst.h = (int)(rect.h * camera.zoom);

    SDL_Point point;
    point.x = (int)(center.x * camera.zoom);
    point.y = (int)(center.y * camera.zoom);

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (flipX && flipY) {
        flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    }
    else if (flipY) {
        flip = SDL_FLIP_VERTICAL;
    }
    else if (flipX) {
        flip = SDL_FLIP_HORIZONTAL;
    }
    SDL_RenderCopyEx(settings::renderer, GetTexture(texName), NULL, &dst, angle, &point, flip);
}

void Textures::DrawRect(SDL_Color color, OBJRECT rect) {
    CAMERA camera = cameraP->GetCam();
    double pivotX = settings::baseW / 2.0;
    double pivotY = settings::baseH / 2.0;
    SDL_Rect dst;
    dst.x = (int)((rect.x - rect.w * 0.5 - (camera.x - pivotX + camera.offsetX + settings::baseW * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
    dst.y = (int)(settings::baseH - ((rect.y + rect.h * 0.5) - (camera.y - pivotY + camera.offsetY + settings::baseH * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
    dst.w = (int)(rect.w * camera.zoom);
    dst.h = (int)(rect.h * camera.zoom);
    SDL_SetRenderDrawColor(settings::renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(settings::renderer, &dst);
}

SDL_Texture* Textures::GetTexture(std::string name) {
    if (map.count(name) == 0) {
        return map["missing"];
    }
    else {
        return map[name];
    }
}

void Textures::DrawTextA(std::string text, SDL_Color color, int x, int y, int w, int h) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(settings::renderer, surface);
    SDL_Rect dst = { x,y,surface->w * w, surface->h * h};
    SDL_RenderCopy(settings::renderer, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Textures::Update() {
}
