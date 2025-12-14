#pragma once
#include<vector>
#include"structs.h"
#include<string>

class Textures;

class Level
{
private:
    std::vector<BLOCKROOM> rooms;
    double blockSize;
public:
    static Textures* texturesP;
    Level();
    void DrawMap();
    OBJRECT IsTouching(OBJRECT obj1);
    double GetBlockSize();
};

