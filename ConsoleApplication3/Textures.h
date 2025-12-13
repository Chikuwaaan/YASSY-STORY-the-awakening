#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include <iostream>
#include "structs.h"

class Textures {
private:
    std::map<std::string, SDL_Texture*> map;
public:
    Textures();
    void LoadTextures();
    void DrawImage(std::string texName, OBJRECT rect, CAMERA camera);
    SDL_Texture* GetTexture(std::string name);
    void Update();
};