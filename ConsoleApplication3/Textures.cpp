#include "Textures.h"
#include "namespace.h"
#include "Camera.h"
#include <cmath>

Camera* Textures::cameraP = nullptr;
SDL_Renderer* r = settings::renderer;
namespace fs = std::filesystem;

Textures::Textures() {
    LoadTextures("Assets/textures");
    //SDL_SetTextureAlphaMod(map["circle_mask"], 127);
    font = TTF_OpenFont("C:/Windows/Fonts/meiryo.ttc", 50);
}

void Textures::LoadTextures(fs::path directoryPath) {
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            std::string ext = entry.path().extension().string();

            if (ext == ".png") {
                std::string filePath = entry.path().string();
                std::string key = entry.path().stem().string();
                const char* c = filePath.c_str();

                if (map.count(key) == 0) {
                    map[key] = IMG_LoadTexture(settings::renderer, c);
                }
                else {
                    std::cout << "[DEBUG]テクスチャの読み込みに失敗しました：ファイル名が重複しています" << filePath << std::endl;
                }
            }
            
        }
        else if (entry.is_directory()) {
            LoadTextures(entry.path());
        }
    }

    /*
    for (auto [_, value] : map) {
        SDL_DestroyTexture(value);
    }
    map["missing"] = IMG_LoadTexture(settings::renderer, "Assets/textures/missing.png");
    map["legL"] = IMG_LoadTexture(r, "Assets/textures/legL.png");
    map["legR"] = IMG_LoadTexture(r, "Assets/textures/legR.png");
    map["body"] = IMG_LoadTexture(r, "Assets/textures/body.png");
    map["head"] = IMG_LoadTexture(r, "Assets/textures/head.png");
    map["armL"] = IMG_LoadTexture(r, "Assets/textures/armL.png");
    map["armR"] = IMG_LoadTexture(r, "Assets/textures/armR.png");
    map["unko"] = IMG_LoadTexture(r, "Assets/textures/unko.png");

    map["BG1"] = IMG_LoadTexture(r, "Assets/textures/untitled.png");

    map["1-0000"] = IMG_LoadTexture(r, "Assets/textures/blocks/1/1-0000.png");
    map["1-0001"] = IMG_LoadTexture(r, "Assets/textures/blocks/1/1-0001.png");
    map["1-0010"] = IMG_LoadTexture(r, "Assets/textures/blocks/1/1-0010.png");
    map["1-0011"] = IMG_LoadTexture(r, "Assets/textures/blocks/1/1-0011.png");
    map["1-0100"] = IMG_LoadTexture(r, "Assets/textures/blocks/1/1-0100.png");
    map["1-0101"] = IMG_LoadTexture(r, "Assets/textures/blocks/1/1-0101.png");
    map["1-0110"] = IMG_LoadTexture(r, "Assets/textures/blocks/1/1-0110.png");
    map["1-1000"] = IMG_LoadTexture(r, "Assets/textures/blocks/1/1-1000.png");
    map["1-1001"] = IMG_LoadTexture(r, "Assets/textures/blocks/1/1-1001.png");
    map["1-1010"] = IMG_LoadTexture(r, "Assets/textures/blocks/1/1-1010.png");
    map["1-1100"] = IMG_LoadTexture(r, "Assets/textures/blocks/1/1-1100.png");
    map["1-1111"] = IMG_LoadTexture(r, "Assets/textures/blocks/1/1-1111.png");
    map["1-0111"] = IMG_LoadTexture(r, "Assets/textures/blocks/1/1-0111.png");
    map["1-1110"] = IMG_LoadTexture(r, "Assets/textures/blocks/1/1-1110.png");
    map["1-1101"] = IMG_LoadTexture(r, "Assets/textures/blocks/1/1-1101.png");
    map["1-1011"] = IMG_LoadTexture(r, "Assets/textures/blocks/1/1-1011.png");

    map["2-0"] = IMG_LoadTexture(r, "Assets/textures/blocks/2-0.png");
    map["2-2"] = IMG_LoadTexture(r, "Assets/textures/blocks/2-2.png");
    map["2-8"] = IMG_LoadTexture(r, "Assets/textures/blocks/2-8.png");
    map["2-10"] = IMG_LoadTexture(r, "Assets/textures/blocks/2-10.png");
    std::cout << "[DEBUG]テクスチャをロードしました" << std::endl;
    */
    
}

SDL_Texture* Textures::GetTexture(std::string name) {
    if (map.count(name) == 0) {
        return map["missing"];
    }
    else {
        return map[name];
    }
}

SDL_Rect Textures::GetDst(OBJRECT rect, bool relative) {
    CAMERA camera = cameraP->GetCam();
    SDL_Rect dst;
    if (relative) {
        double pivotX = settings::baseW / 2.0;
        double pivotY = settings::baseH / 2.0;
        dst.x = (int)round((rect.x - rect.w * 0.5 - (camera.x - pivotX + camera.offsetX + settings::baseW * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
        dst.y = (int)round(settings::baseH - ((rect.y + rect.h * 0.5) - (camera.y - pivotY + camera.offsetY + settings::baseH * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
        dst.w = (int)round(rect.w * camera.zoom);
        dst.h = (int)round(rect.h * camera.zoom);
    }
    else {
        dst.x = (int)round(rect.x);
        dst.y = (int)round(rect.y);
        dst.w = (int)round(rect.w);
        dst.h = (int)round(rect.h);
    }

    return dst;
}

void Textures::DrawImage(std::string texName, OBJRECT rect, bool relative, ROTATE rotate) {
    CAMERA camera = cameraP->GetCam();
    SDL_Rect dst = GetDst(rect, relative);

    if (rotate.rotate) {
        SDL_Point point;
        point.x = (int)(rotate.centerX * camera.zoom);
        point.y = (int)(rotate.centerY * camera.zoom);
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if (rotate.flipX && rotate.flipY) {
            flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
        }
        else if (rotate.flipY) {
            flip = SDL_FLIP_VERTICAL;
        }
        else if (rotate.flipX) {
            flip = SDL_FLIP_HORIZONTAL;
        }
        SDL_RenderCopyEx(settings::renderer, GetTexture(texName), NULL, &dst, rotate.angle, &point, flip);
    }
    else {
        SDL_RenderCopy(settings::renderer, GetTexture(texName), NULL, &dst);
    }
}

void Textures::DrawRect(SDL_Color color, OBJRECT rect, bool relative) {
    SDL_SetRenderTarget(r, nullptr);
    SDL_Rect dst = GetDst(rect, relative);

    SDL_SetRenderDrawColor(settings::renderer, color.r, color.g, color.b, color.a);
    if (rect.block) {
        SDL_RenderFillRect(settings::renderer, &dst);
    }
    else {
        SDL_RenderDrawRect(settings::renderer, &dst);
    }
}

void Textures::DrawTexts(std::string text, SDL_Color color, OBJRECT rect, bool relative, ROTATE rotate) {
    CAMERA camera = cameraP->GetCam();
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(settings::renderer, surface);
    SDL_Rect dst;
    if (relative) {
        double pivotX = settings::baseW / 2.0;
        double pivotY = settings::baseH / 2.0;
        dst.x = (int)round((rect.x - rect.w * 0.5 - (camera.x - pivotX + camera.offsetX + settings::baseW * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
        dst.y = (int)round(settings::baseH - ((rect.y + rect.h * 0.5) - (camera.y - pivotY + camera.offsetY + settings::baseH * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
        dst.w = (int)round(surface->w * rect.w * camera.zoom);
        dst.h = (int)round(surface->h * rect.h * camera.zoom);
    }
    else {
        dst.x = (int)round(rect.x);
        dst.y = (int)round(rect.y);
        dst.w = (int)round(surface->w * rect.w);
        dst.h = (int)round(surface->h * rect.h);
    }

    
    if (rotate.rotate) {
        SDL_Point point;
        point.x = (int)(rotate.centerX * camera.zoom);
        point.y = (int)(rotate.centerY * camera.zoom);
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if (rotate.flipX && rotate.flipY) {
            flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
        }
        else if (rotate.flipY) {
            flip = SDL_FLIP_VERTICAL;
        }
        else if (rotate.flipX) {
            flip = SDL_FLIP_HORIZONTAL;
        }
        SDL_RenderCopyEx(settings::renderer, texture, NULL, &dst, rotate.angle, &point, flip);
    }
    else {
        SDL_RenderCopy(settings::renderer, texture, NULL, &dst);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Textures::Update() {
    ModTextures();
}

void Textures::ModTextures() {
    for (const auto& [key, value] : map) {
        if (key.size() == 0) continue;
        char c1 = key[0];

        if (c1 == '1') {
            SDL_Color rainbow = utilities::HSVtoRGB(platformer::flames % 360, 0.2, 1, 255);
            SDL_SetTextureColorMod(value, rainbow.r, rainbow.g, rainbow.b);
        }
    }
}
