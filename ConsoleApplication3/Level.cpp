#include "Level.h"
#include "Textures.h"
#include "namespace.h"

Textures* Level::texturesP = nullptr;

Level::Level() {
    blockSize = 90.0;
    rooms.push_back({ 0,0,{
            {0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,1,0,1,0,1,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0},
            {0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,1,1,0,0,1,0,0,0,1,0,0,0,1,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0},
            {0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,1,1,0,0,0,1,0,0},
            {0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
} });
    rooms.push_back({ -1,0,{
        {0,0,2},
        {0,0,0},
        {2,0,0}
} });
    rooms.push_back({ 32,9,{
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,2,2,2},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,2,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,2,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {2,2,2,0,0,0,0,0,0},
} });
    rooms.push_back({ 49,5,{
        {2}
} });
}

void Level::DrawMap() {
    const int room = (int)rooms.size();

    for (int h = 0; h < room; h++) {
        int row = (int)rooms[h].terrain.size();
        int column = (int)rooms[h].terrain[0].size();
        for (int i = 0; i < row; i++) {
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
                    //DrawImage(texturesP->getTexture("unko"), obj2, cameraP->getCam(), 0, 0, 0, 0, 0);
                    //std::cout << obj2.x << "," << obj2.y << std::endl;
                    a = utilities::HitDetection(obj1, obj2);
                    if (a) {
                        return { blockSize * (j + levelX + 0.5), blockSize * (row - (i - levelY + 0.5)), blockSize, blockSize, true };
                    }
                }
            }
        }
    }


    return { 0, 0, 0, 0, false };
}

double Level::GetBlockSize() {
    return blockSize;
}