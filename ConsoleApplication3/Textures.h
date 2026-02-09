#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <map>
#include <iostream>
#include <filesystem>
#include "structs.h"

class Camera;

enum class Icons;
enum class Anchor {
    Center,
    Left
};

class Textures {
private:
    TTF_Font* font;
    TTF_Font* fontb;
    std::map<std::string, SDL_Texture*> map;
    std::map<Icons, SDL_Point> iconProperty;
public:
    
    static Camera* cameraP;
    Textures();
    void LoadTextures(std::filesystem::path directoryPath);
    SDL_Texture* GetTexture(std::string name);
    SDL_Rect GetTexRect(std::string name);
    SDL_Rect GetDst(OBJRECT rect, bool relative, Anchor anchor);
    void DrawImage(std::string texName, OBJRECT rect, bool relative, ROTATE rotate);
    void DrawImageS(std::string texName, SDL_Rect rect, bool relative, ROTATE rotate);
    void DrawSprite(std::string sheet, OBJRECT rect, SDL_Rect src, bool relative);
    void DrawIcon(Icons icon, SDL_Rect rect);
    void DrawRect(SDL_Color color, OBJRECT rect, bool relative);
    void DrawTexts(std::string text, SDL_Color col1, SDL_Color col2, OBJRECT rect, bool relative, Anchor anchor);
    void Update();
    void ModTextures();
};