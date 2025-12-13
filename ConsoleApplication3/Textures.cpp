#include "Textures.h"
#include "namespace.h"
#include "Camera.h"

Textures::Textures() {
    LoadTextures();
}

void Textures::LoadTextures() {
    for (auto [_, value] : map) {
        SDL_DestroyTexture(value);
    }
    map["missing"] = IMG_LoadTexture(settings::renderer, "Assets/textures/missing.png");
    map["1"] = IMG_LoadTexture(settings::renderer, "Assets/textures/BAN.png");
    map["2"] = IMG_LoadTexture(settings::renderer, "Assets/textures/dokufee.png");
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

    std::cout << "[DEBUG]テクスチャをロードしました";
}

void Textures::DrawImage(std::string texName, OBJRECT rect, CAMERA camera) {
    double pivotX = settings::baseW / 2.0;
    double pivotY = settings::baseH / 2.0;
    SDL_Rect dst;
    dst.x = (int)((rect.x - rect.w * 0.5 - (camera.x - pivotX + settings::baseW * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
    dst.y = (int)(settings::baseH - ((rect.y + rect.h * 0.5) - (camera.y - pivotY + settings::baseH * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
    dst.w = (int)(rect.w * camera.zoom);
    dst.h = (int)(rect.h * camera.zoom);
    SDL_RenderCopy(settings::renderer, GetTexture(texName), NULL, &dst);
}

SDL_Texture* Textures::GetTexture(std::string name) {
    if (map.count(name) == 0) {
        return map["missing"];
    }
    else {
        return map[name];
    }
}

void Textures::Update() {
}