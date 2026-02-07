#include "Textures.h"
#include "namespace.h"
#include "Camera.h"
#include <cmath>
#include "iconProperty.h"

Camera* Textures::cameraP = nullptr;
SDL_Renderer* r = settings::renderer;
namespace fs = std::filesystem;

enum class Anchor {
    TopLeft,
    Center
};

Textures::Textures() {
    LoadTextures("Assets/textures");

    //FONTS
    std::cout << "loading fonts..." << std::endl;
    font = TTF_OpenFont("C:/Windows/Fonts/meiryo.ttc", 50);
    if (font) {
        std::cout << "[DEBUG]標準フォントを読み込みました" << std::endl;
    }
    fontb = TTF_OpenFont("C:/Windows/Fonts/meiryo.ttc", 50);
    if (fontb) {
        std::cout << "[DEBUG]太字フォントを読み込みました" << std::endl;
        TTF_SetFontOutline(fontb, 5);
    }

    if (map.count("icons") == 1) {
        iconProperty[Icons::Back] = { 0,0 };
        iconProperty[Icons::Next] = { 1,0 };
        iconProperty[Icons::UO] = { 3,3 };
        iconProperty[Icons::Clear] = { 0,1 };
        iconProperty[Icons::uo] = { 3,0 };
    }
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

    

}

SDL_Texture* Textures::GetTexture(std::string name) {
    if (map.count(name) == 0) {
        return map["missing"];
    }
    else {
        return map[name];
    }
}

SDL_Rect Textures::GetTexRect(std::string name) {
    SDL_Rect rect;
    int w, h;
    SDL_Texture* tex = GetTexture(name);

    SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
    rect = { 0, 0, w, h };
    return rect;
}

SDL_Rect Textures::GetDst(OBJRECT rect, bool relative) {
    CAMERA camera;
    SDL_Rect dst;
    if (relative) {
        camera = cameraP->GetCam();
    }
    else {
        camera = { settings::baseW / 2.0 , settings::baseH / 2.0 , 0, 0, settings::baseW / 2.0 , settings::baseH / 2.0, 1 };
    }
    double pivotX = settings::baseW / 2.0;
    double pivotY = settings::baseH / 2.0;
    dst.x = (int)round((rect.x - rect.w * 0.5 - (camera.x - pivotX + camera.offsetX + settings::baseW * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
    dst.y = (int)round(settings::baseH - ((rect.y + rect.h * 0.5) - (camera.y - pivotY + camera.offsetY + settings::baseH * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
    dst.w = (int)round(rect.w * camera.zoom);
    dst.h = (int)round(rect.h * camera.zoom);

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

void Textures::DrawImageS(std::string texName, SDL_Rect Rect, bool relative, ROTATE rotate) {
    CAMERA camera = cameraP->GetCam();
    OBJRECT rect;
    rect.x = (double)Rect.x;
    rect.y = (double)Rect.y;
    rect.w = (double)Rect.w;
    rect.h = (double)Rect.h;
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

void Textures::DrawSprite(std::string sheet, OBJRECT rect, SDL_Rect src) {
    CAMERA camera = cameraP->GetCam();
    SDL_Rect dst = GetDst(rect, 0);
    SDL_RenderCopy(settings::renderer, GetTexture(sheet), &src, &dst);
}

void Textures::DrawIcon(Icons icon, SDL_Rect rect) {
    int gridSize = 16;

    OBJRECT dst;
    dst.x = (int)rect.x;
    dst.y = (int)rect.y;
    dst.w = (int)rect.w;
    dst.h = (int)rect.h;

    SDL_Rect src;
    src.x = gridSize * iconProperty[icon].x;
    src.y = gridSize * iconProperty[icon].y;
    src.w = gridSize;
    src.h = gridSize;

    DrawSprite("icons", dst, src);
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

void Textures::DrawTexts(std::string text, SDL_Color col1, SDL_Color col2, OBJRECT rect, bool relative, ROTATE rotate) {
    CAMERA camera = cameraP->GetCam();
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), col1);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(settings::renderer, surface);
    SDL_Surface* surfaceb = TTF_RenderText_Blended(fontb, text.c_str(), col2);
    SDL_Texture* textureb = SDL_CreateTextureFromSurface(settings::renderer, surfaceb);
    SDL_Rect dst1;
    SDL_Rect dst2;

    if (relative) {
        double pivotX = settings::baseW / 2.0;
        double pivotY = settings::baseH / 2.0;
        dst1.x = (int)round((rect.x - rect.w * 0.5 - (camera.x - pivotX + camera.offsetX + settings::baseW * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
        dst1.y = (int)round(settings::baseH - ((rect.y + rect.h * 0.5) - (camera.y - pivotY + camera.offsetY + settings::baseH * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
        dst1.w = (int)round(surface->w * rect.w * camera.zoom);
        dst1.h = (int)round(surface->h * rect.h * camera.zoom);

        dst2 = dst1;
        dst2.w = (int)round(surfaceb->w * rect.w * camera.zoom);
        dst2.h = (int)round(surfaceb->h * rect.h * camera.zoom);
    }
    else {
        dst1.x = (int)round(rect.x);
        dst1.y = (int)round(rect.y);
        dst1.w = (int)round(surface->w * rect.w);
        dst1.h = (int)round(surface->h * rect.h);

        dst2 = dst1;
        dst2.x += (int)round((dst1.w - (surfaceb->w * rect.w)) / 2);
        dst2.y += (int)round((dst1.h - (surfaceb->h * rect.h)) / 2);
        dst2.w = (int)round(surfaceb->w * rect.w);
        dst2.h = (int)round(surfaceb->h * rect.h);
        //dst2.w = (int)round((dst1.w - (surfaceb->w * rect.w)) / 2.0 + (surfaceb->w * rect.w));
        //dst2.h = (int)round((dst1.h - (surfaceb->h * rect.h)) / 2.0 + (surfaceb->h * rect.h));

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
        SDL_RenderCopyEx(settings::renderer, textureb, NULL, &dst2, rotate.angle, &point, flip);
        SDL_RenderCopyEx(settings::renderer, texture, NULL, &dst1, rotate.angle, &point, flip);
    }
    else {
        SDL_RenderCopy(settings::renderer, textureb, NULL, &dst2);
        SDL_RenderCopy(settings::renderer, texture, NULL, &dst1);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(textureb);
    SDL_FreeSurface(surfaceb);
}

void Textures::Update() {
    //ModTextures();
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
