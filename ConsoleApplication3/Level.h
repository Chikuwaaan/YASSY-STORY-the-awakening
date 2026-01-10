#pragma once
#include<vector>
#include"structs.h"
#include "Camera.h"
#include<string>
#include <map>

class Textures;
class Camera;

class Level
{
private:
    std::vector<BLOCK> blockProperty;
    std::vector<BLOCKROOM> rooms;
    int levelW, levelH;
    uint8_t level[32][128];
    double blockSize;
    int editorPalette;
public:
    static Textures* texturesP;
    static Input* inputP;
    static Camera* cameraP;
    Level();
    void FileOutput();

    void LoadLevel(int n);
    void LoadMap(int n);

    void Editor();
    void DrawMap();
    std::string GetTexName(int block, int mask);
    int CheckAroundTile(int y, int x, CHECKFOR checkFor);
    bool CheckTile(int y, int x);
    OBJRECT IsTouching2(OBJRECT obj1, bool direction);
    void FixBlockPos(int* x, int* y);
};

