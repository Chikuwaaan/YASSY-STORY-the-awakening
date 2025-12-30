#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <map>
#include <iostream>
#include "structs.h"

class Camera;

class Textures {
private:
    std::map<std::string, SDL_Texture*> map;
    TTF_Font* font;
public:
    static Camera* cameraP;
    Textures();
    void LoadTextures();
    SDL_Texture* GetTexture(std::string name);
    SDL_Rect GetDst(OBJRECT rect, bool relative);
    void DrawImage(std::string texName, OBJRECT rect, bool relative, ROTATE rotate);
    void DrawRect(SDL_Color color, OBJRECT rect, bool relative);
    void DrawTexts(std::string text, SDL_Color color, OBJRECT rect, bool relative, ROTATE rotate);
    void Update();
};