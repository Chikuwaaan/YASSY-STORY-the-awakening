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
    void DrawImage(std::string texName, OBJRECT rect);
    void DrawImageEx(std::string texName, OBJRECT rect, double angle, OBJRECT center, bool flipX, bool flipY);
    void DrawRect(SDL_Color color, OBJRECT rect);
    SDL_Texture* GetTexture(std::string name);
    void DrawTextA(std::string text, SDL_Color color, int x, int y, int w, int h);
    void Update();
};