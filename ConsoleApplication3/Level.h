#pragma once
#include<vector>
#include"structs.h"
#include<string>

class Textures;

class Level
{
private:
    std::vector<BLOCKROOM> rooms;
    int levelW, levelH;
    uint8_t level[32][128];
    double blockSize;
public:
    static Textures* texturesP;
    Level();
    void SetLevel();
    void FileOutput();
    void FileInput();
    void DrawMap();
    OBJRECT IsTouching2(OBJRECT obj1, bool direction);
    void FixBlockPos(int* x, int* y);
};

