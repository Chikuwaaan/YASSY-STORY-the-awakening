#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <map>
#include <iostream>
#include <filesystem>
#include "structs.h"
#include "Timer.h"

class Camera;

enum class Icons;
enum class Anchor {
    Center,
    Left
};

struct ROTATE {
    bool rotate;
    double angle;
    double centerX;
    double centerY;
    bool flipX;
    bool flipY;
};

class Textures {
private:
    TTF_Font* font;
    TTF_Font* fontb;
    std::map<std::string, SDL_Texture*> map;
    std::map<Icons, SDL_Point> iconProperty;
    SDL_Texture* canvas;
    SDL_Texture* blur;
    Timer timer;
public:
    static Camera* cameraP;
    Textures();
    void LoadTextures(std::filesystem::path directoryPath);
    SDL_Texture* GetCanvas();
    SDL_Texture* GetTexture(std::string name);
    SDL_Rect GetTexRect(std::string name);
    SDL_Rect GetDst(OBJRECT rect, bool relative, Anchor anchor);
    void DrawImage(std::string texName, OBJRECT rect, bool relative, ROTATE rotate);
    void DrawImageA(std::string texName, OBJRECT rect, bool relative, Anchor anchor);
    void DrawImageS(std::string texName, SDL_Rect rect, bool relative, ROTATE rotate);
    void DrawSprite(std::string sheet, OBJRECT rect, SDL_Rect src, bool relative);
    void DrawIcon(Icons icon, SDL_Rect rect);
    void DrawRect(SDL_Color color, OBJRECT rect, bool relative);
    void DrawLine(SDL_Color color, POSITION p1, POSITION p2, bool relative);
    void DrawTexts(std::string text, SDL_Color col1, SDL_Color col2, OBJRECT rect, bool relative, Anchor anchor);
    void DrawTexts(std::u8string text, SDL_Color col1, SDL_Color col2, OBJRECT rect, bool relative, Anchor anchor);
    void Update();
    void Blur(double angle, double distance, double alpha);
    void ModTextures();
};