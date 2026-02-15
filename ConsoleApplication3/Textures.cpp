#include "Textures.h"
#include "namespace.h"
#include "Camera.h"
#include <cmath>
#include "iconProperty.h"

Camera* Textures::cameraP = nullptr;
SDL_Renderer* r = settings::renderer;
namespace fs = std::filesystem;


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
        iconProperty[Icons::Null] = { -1,0 };
        iconProperty[Icons::Zero] = { 0,0 };
        iconProperty[Icons::One] = { 1,0 };
        iconProperty[Icons::Two] = { 2,0 };
        iconProperty[Icons::Three] = { 3,0 };
        iconProperty[Icons::Four] = { 4,0 };
        iconProperty[Icons::Five] = { 5,0 };
        iconProperty[Icons::Six] = { 6,0 };
        iconProperty[Icons::Seven] = { 7,0 };
        iconProperty[Icons::Eight] = { 8,0 };
        iconProperty[Icons::Nine] = { 9,0 };
        iconProperty[Icons::ZeroB] = { 0,1 };
        iconProperty[Icons::OneB] = { 1,1 };
        iconProperty[Icons::TwoB] = { 2,1 };
        iconProperty[Icons::ThreeB] = { 3,1 };
        iconProperty[Icons::FourB] = { 4,1 };
        iconProperty[Icons::FiveB] = { 5,1 };
        iconProperty[Icons::SixB] = { 6,1 };
        iconProperty[Icons::SevenB] = { 7,1 };
        iconProperty[Icons::EightB] = { 8,1 };
        iconProperty[Icons::NineB] = { 9,1 };

        iconProperty[Icons::ButtonIdle] = { 14,0 };
        iconProperty[Icons::ButtonOnMouse] = { 15,0 };
        iconProperty[Icons::ButtonPressed] = { 14,1 };
        iconProperty[Icons::ButtonUnavailable] = { 15,1 };
        iconProperty[Icons::ButtonMIdle] = { 12,0 };
        iconProperty[Icons::ButtonMOnMouse] = { 13,0 };
        iconProperty[Icons::ButtonMPressed] = { 12,1 };
        iconProperty[Icons::ButtonMUnavailable] = { 13,1 };
        iconProperty[Icons::ButtonLIdle] = { 12,2 };
        iconProperty[Icons::ButtonLOnMouse] = { 13,2 };
        iconProperty[Icons::ButtonLPressed] = { 12,3 };
        iconProperty[Icons::ButtonLUnavailable] = { 13,3 };
        iconProperty[Icons::ButtonRIdle] = { 14,2 };
        iconProperty[Icons::ButtonROnMouse] = { 15,2 };
        iconProperty[Icons::ButtonRPressed] = { 14,3 };
        iconProperty[Icons::ButtonRUnavailable] = { 15,3 };
        iconProperty[Icons::UICursor1] = { 11,0 };
        iconProperty[Icons::UICursor2] = { 10,0 };
        iconProperty[Icons::UICursor3] = { 10,1 };
        iconProperty[Icons::UICursor4] = { 11,1 };


        iconProperty[Icons::Back] = { 0,2 };
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

SDL_Rect Textures::GetDst(OBJRECT rect, bool relative, Anchor anchor) {
    CAMERA camera;
    SDL_Rect dst = {0,0,0,0};
    if (relative) {
        camera = cameraP->GetCam();
    }
    else {
        camera = { settings::baseW / 2.0 , settings::baseH / 2.0 , 0, 0, settings::baseW / 2.0 , settings::baseH / 2.0, 1 };
    }

    if (anchor == Anchor::Center) {
        double pivotX = settings::baseW / 2.0;
        double pivotY = settings::baseH / 2.0;
        dst.x = (int)round((rect.x - rect.w * 0.5 - (camera.x - pivotX + camera.offsetX + settings::baseW * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
        dst.y = (int)round(settings::baseH - ((rect.y + rect.h * 0.5) - (camera.y - pivotY + camera.offsetY + settings::baseH * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
        dst.w = (int)round(rect.w * camera.zoom);
        dst.h = (int)round(rect.h * camera.zoom);
    }
    else if (anchor == Anchor::Left) {
        double pivotX = settings::baseW / 2.0;
        double pivotY = settings::baseH / 2.0;
        dst.x = (int)round((rect.x - (camera.x - pivotX + camera.offsetX + settings::baseW * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
        dst.y = (int)round(settings::baseH - ((rect.y + rect.h * 0.5) - (camera.y - pivotY + camera.offsetY + settings::baseH * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
        dst.w = (int)round(rect.w * camera.zoom);
        dst.h = (int)round(rect.h * camera.zoom);
    }
    

    return dst;
}

void Textures::DrawImage(std::string texName, OBJRECT rect, bool relative, ROTATE rotate) {
    CAMERA camera = cameraP->GetCam();
    SDL_Rect dst = GetDst(rect, relative, Anchor::Center);

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
    SDL_Rect dst = GetDst(rect, relative, Anchor::Center);

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

void Textures::DrawSprite(std::string sheet, OBJRECT rect, SDL_Rect src, bool relative) {
    CAMERA camera = cameraP->GetCam();
    SDL_Rect dst = GetDst(rect, relative, Anchor::Center);
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

    DrawSprite("icons", dst, src, 0);
}

void Textures::DrawRect(SDL_Color color, OBJRECT rect, bool relative) {
    SDL_SetRenderTarget(r, nullptr);
    SDL_Rect dst = GetDst(rect, relative, Anchor::Center);

    SDL_SetRenderDrawColor(settings::renderer, color.r, color.g, color.b, color.a);
    if (rect.block) {
        SDL_RenderFillRect(settings::renderer, &dst);
    }
    else {
        SDL_RenderDrawRect(settings::renderer, &dst);
    }
}

void Textures::DrawTexts(std::string text, SDL_Color col1, SDL_Color col2, OBJRECT rect, bool relative, Anchor anchor) {
    CAMERA camera = cameraP->GetCam();
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), col1);
    if (!surface) return;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(settings::renderer, surface);
    SDL_Surface* surfaceb = TTF_RenderText_Blended(fontb, text.c_str(), col2);
    if (!surfaceb) return;
    SDL_Texture* textureb = SDL_CreateTextureFromSurface(settings::renderer, surfaceb);
    OBJRECT rect1 = {rect.x, rect.y, surface->w * rect.w, surface->h * rect.h};
    SDL_Rect dst1 = GetDst(rect1, relative, anchor);
    OBJRECT rect2;
    rect2 = rect1;
    if (anchor == Anchor::Left) {
        rect2.x = rect1.x + (surface->w * rect.w / 2);
    }
    rect2.w = surfaceb->w * rect.w;
    rect2.h = surfaceb->h * rect.h;
    SDL_Rect dst2 = GetDst(rect2, relative, Anchor::Center);

    SDL_RenderCopy(settings::renderer, textureb, NULL, &dst2);
    SDL_RenderCopy(settings::renderer, texture, NULL, &dst1);
    
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
