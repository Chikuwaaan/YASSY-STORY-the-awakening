#pragma once
#include<vector>
#include"structs.h"
#include<string>

class Textures;

class Level
{
private:
    std::vector<BLOCKROOM> rooms;
    uint8_t level[32][64];
    double blockSize;
public:
    static Textures* texturesP;
    Level();
    void SetLevel();
    void DrawMap();
    OBJRECT IsTouching(OBJRECT obj1);
    OBJRECT IsTouching2(OBJRECT obj1, bool direction);
    void FixBlockPos(int* x, int* y);
};

