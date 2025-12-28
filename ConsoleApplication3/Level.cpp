#include "Level.h"
#include "Textures.h"
#include "namespace.h"
#include <cmath>

Textures* Level::texturesP = nullptr;

Level::Level() {
    blockSize = 80.0;
    rooms.push_back({ 0,0,{
        {1,1,1,1,1,1,1,1,1,1}
} });

    /*
    rooms.push_back({ 0,0,{
        {0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,3,0,0,0,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,1,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,1,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,3,3,3,3,3,3,3,3,4,4,0,0,0,0,0,0,0},
        {1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,4,4,3,3,1},
        {1,1,1,2,1,1,1,4,4,4,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1}
} });
    rooms.push_back({ 1,1,{
        {4,0},
        {0},
        {0},
        {4,4},
}});
    rooms.push_back({ 32,0,{
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,3,3,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,3,0,0,0,3,3,0,0,0,0,3,0,0,0,0,0,3,3,0,0,0},
        {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,0,1,0,1,0,1,0,4,0,1,2,2,2,1,0,0,0,0,4,2,0,1}
} });
    */
    /*
    rooms.push_back({ -3,0,{
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,3,1,1,1,4,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,2,1,1,1,4,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
} });

    rooms.push_back({ 0,0,{
            {0,0,1,1,1,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,1,0,1,0,1,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,2,0,2,0},
            {0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,1,1,0,0,1,0,0,0,1,0,0,0,1,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0},
            {0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,1,1,0,0,0,1,0,0},
            {0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
} });
    rooms.push_back({ -1,0,{
        {0,0,2},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {2,0,0}
} });
    rooms.push_back({ 2,13,{
        {3,3,3}
} });
    rooms.push_back({ 32,9,{
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,2,2,3},
        {0,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,2,0,0},
        {4,4,4,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,2,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {2,2,2,0,0,0,0,0,0},
} });
    rooms.push_back({ 49,5,{
        {0,0,0,3,3,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,3,0,3,0,0},
        {0,0,0,0,0,0,0,0,0,0,3,0,3,0,0},
        {2,2,2,2,2,1,1,1,1,1,1,1,1,1,1}
} });
    rooms.push_back({ 65,5,{
        {0,2,0,2,0},
        {0,0,0,0,0},
        {2,0,0,0,2},
        {0,2,2,2,0}
} });
*/
    SetLevel();
}

void Level::SetLevel() {

    for (int h = 0; h < rooms.size(); h++) {
        BLOCKROOM room = rooms[h];
        for (int i = 0; i < room.terrain.size(); i++) {
            for (int j = 0; j < room.terrain[i].size(); j++) {
                level[i + room.y][j + room.x] = room.terrain[room.terrain.size() - 1 - i][j];
            }
        }
        //std::cout << std::endl;
    }
    
    for (int i = 0; i < std::size(level); i++) {
        for (int j = 0; j < std::size(level[0]); j++) {
            //std::cout << std::to_string(level[i][j]);
        }
        //std::cout << std::endl;
    }
}

void Level::DrawMap() {
    const int room = (int)rooms.size();

    for (int h = 0; h < room; h++) {
        int row = (int)rooms[h].terrain.size();
        for (int i = 0; i < row; i++) {
            int column = (int)rooms[h].terrain[i].size();
            for (int j = 0; j < column; j++) {
                std::string texName = std::to_string(rooms[h].terrain[i][j]);
                if (texName != "0") {
                    OBJRECT rect;
                    rect.x = blockSize * (j + 0.5) + blockSize * rooms[h].x;
                    rect.y = blockSize * (row - (i + 0.5)) + blockSize * rooms[h].y;
                    rect.w = blockSize;
                    rect.h = blockSize;
                    texturesP->DrawImage(texName, rect);
                }
            }
        }
    }

};

OBJRECT Level::IsTouching(OBJRECT obj1) {
    bool a = false;
    const int room = (int)rooms.size();
    const int width = (int)(obj1.w / blockSize) + 1;
    const int height = (int)(obj1.h / blockSize) + 1;

    for (int h = 0; h < room; h++) {
        int row = (int)rooms[h].terrain.size();
        int column = (int)rooms[h].terrain[0].size();
        int levelX = rooms[h].x;
        int levelY = rooms[h].y;
        int playerLevelX = (int)(obj1.x / blockSize) - levelX;
        int playerLevelY = row - (int)(obj1.y / blockSize) - 1 + levelY;

        int i = playerLevelY - height;
        int j;
        int k = playerLevelY + height;
        int l = playerLevelX + width;
        if (i < 0) i = 0;
        if (k > (row - 1)) k = row - 1;
        for (; i <= k; i++) {
            j = playerLevelX - width;
            if (j < 0) j = 0;
            if (l > (column - 1)) l = column - 1;

            for (; j <= l; j++) {
                if (rooms[h].terrain[i][j] != 0) {
                    OBJRECT obj2 = { blockSize * (j + levelX + 0.5) , blockSize * (row - (i - levelY + 0.5)) , blockSize, blockSize };
                    a = utilities::HitDetection(obj1, obj2);
                    if (a) {
                        return { blockSize * (j + levelX + 0.5), blockSize * (row - (i - levelY + 0.5)), blockSize, blockSize, rooms[h].terrain[i][j] };
                    }
                }
            }
        }
    }


    return { 0, 0, 0, 0, 0 };
}

OBJRECT Level::IsTouching2(OBJRECT obj1, bool direction) {
    SDL_Color color = { 255,255,255,255 };

    int levelX = (int)round((obj1.x - blockSize / 2) / blockSize);
    int extraX = (int)round((obj1.x) / blockSize);
    int levelY = (int)round((obj1.y - blockSize / 2) / blockSize);
    int extraY = (int)round((obj1.y) / blockSize);
    texturesP->DrawTextA(std::to_string(levelX) + " " + std::to_string(levelY), color, 1000, 0, 1, 1);
    texturesP->DrawTextA(std::to_string(extraX) + " " + std::to_string(extraY), color, 1000, 50, 1, 1);

    //0=y, 1=x
    if (!direction) {
        for (int i = -1; i < 2; i += 2) {
            int blockX = levelX;
            int blockY = levelY + i;
            FixBlockPos(&blockX, &blockY);
            int blockType = level[blockY][blockX];
            if (blockType == 0) {
                if (blockX < extraX) {
                    blockX++;
                }
                else if (blockX = extraX) {
                    blockX--;
                }
            }
            FixBlockPos(&blockX, &blockY);
            blockType = level[blockY][blockX];

            if (blockType) {
                OBJRECT obj2;
                obj2.x = (blockX + 0.5) * blockSize;
                obj2.y = (blockY + 0.5) * blockSize;
                obj2.w = blockSize;
                obj2.h = blockSize;
                obj2.block = blockType;
                if (utilities::HitDetection(obj1, obj2)) {
                    return obj2;
                }
            }
        }
    }

    else {
        for (int i = -1; i < 2; i += 2) {
            int blockX = levelX + i;
            int blockY = levelY;
            FixBlockPos(&blockX, &blockY);
            int blockType = level[blockY][blockX];
            if (blockType == 0) {
                if (blockY < extraY) {
                    blockY++;
                }
                else if (blockY = extraY) {
                    blockY--;
                }
            }
            FixBlockPos(&blockX, &blockY);
            blockType = level[blockY][blockX];

            if (blockType) {
                OBJRECT obj2;
                obj2.x = (blockX + 0.5) * blockSize;
                obj2.y = (blockY + 0.5) * blockSize;
                obj2.w = blockSize;
                obj2.h = blockSize;
                obj2.block = blockType;
                if (utilities::HitDetection(obj1, obj2)) {
                    return obj2;
                }
            }
        }
    }
    
    

    return { 0,0,0,0,0 };
}

void Level::FixBlockPos(int* x, int* y) {
    if (*x < 0) {
        *x = 0;
    }
    else if (*x >= std::size(level[0])) {
        *x = std::size(level[0]) - 1;
    }

    if (*y < 0) {
        *y = 0;
    }
    else if (*y >= std::size(level)) {
        *y = std::size(level) - 1;
    }
}