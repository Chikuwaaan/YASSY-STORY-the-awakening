#pragma once
#include<vector>
#include"structs.h"
#include "Camera.h"
#include<string>
#include <map>
#include <SDL.h>

class Textures;
class Camera;
class Game;

enum class CHECKFOR {
    TopRight,
    TopLeft,
    BottomLeft,
    BottomRight
};

class Level
{
private:
    std::vector<BLOCKROOM> rooms;
    int levelW, levelH;
    uint8_t level[32][256];
    double blockSize;
    int editorPalette;
public:
    static Textures* texturesP;
    static Input* inputP;
    static Camera* cameraP;
    static Game* gameP;
    Level();
    void FileOutput(int n);

    void LoadLevel(int n);
    void LoadMap(int n);

    void Editor();
    void DrawMap();
    double GetBlockSize();
    SDL_Rect CheckAroundTile(int y, int x, CHECKFOR checkFor, int type);

    OBJRECT IsTouching2(OBJRECT obj1, bool direction);
    void FixBlockPos(int* x, int* y);
};

