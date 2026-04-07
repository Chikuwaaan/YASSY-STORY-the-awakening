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
class Player;

enum class CHECKFOR {
    TopRight,
    TopLeft,
    BottomLeft,
    BottomRight
};

struct BLOCK {
    std::string tex;
    int renderingType;
    OBJRECT hitBox;
    int damage;
    bool stuck;
    bool invisible;
};

class Level
{
private:
    std::vector<BLOCKROOM> rooms;
    int levelW, levelH;
    uint8_t level[128][1024];
    double blockSize;
    int editorPalette;
    bool dev;
    int mouseX, mouseY;
    double mouseXC, mouseYC;
public:
    static Textures* texturesP;
    static Input* inputP;
    static Camera* cameraP;
    static Game* gameP;
    static Player* playerP;

    std::vector<BLOCK> blockProperty;

    Level();
    void FileOutput(int n);

    void LoadLevel(int n);
    void LoadMap(int n);


    void Update();
    void Editor();
    void DrawMap(bool mode);
    double GetBlockSize();
    SDL_Rect CheckAroundTile1(int y, int x, CHECKFOR checkFor, int type);
    SDL_Rect CheckAroundTile2(int y, int x, int type);
    SDL_Rect CheckAroundTile3(int y, int x, int type);

    OBJRECT IsTouching2(OBJRECT obj1, bool direction);
    void FixBlockPos(int* x, int* y);

    void GetMouseC(double* x, double* y);
};

