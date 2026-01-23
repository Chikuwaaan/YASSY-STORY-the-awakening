#pragma once
#include<vector>
#include"structs.h"
#include "Camera.h"
#include<string>
#include <map>

class Textures;
class Camera;
class Game;

class Level
{
private:
    std::vector<BLOCK> blockProperty;
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
    std::string GetTexName(int block, int mask);
    double GetBlockSize();
    int CheckAroundTile(int y, int x, CHECKFOR checkFor, int type);
    
    bool CheckTile(int y, int x, int type);
    OBJRECT IsTouching2(OBJRECT obj1, bool direction);
    void FixBlockPos(int* x, int* y);
};

