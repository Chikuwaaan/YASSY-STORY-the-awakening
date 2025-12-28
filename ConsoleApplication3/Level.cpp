#include "Level.h"
#include "Textures.h"
#include "namespace.h"
#include "Input.h"
#include "Camera.h"
#include <cmath>
#include <fstream>

Textures* Level::texturesP = nullptr;
Input* Level::inputP = nullptr;
Camera* Level::cameraP = nullptr;

Level::Level() {
    levelW = 128;
    levelH = 32;
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
    FileInput();
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

void Level::FileOutput() {
    std::vector<uint8_t> map;
    map.reserve(levelW * levelH);

    for (int y = 0; y < levelH; y++) {
        for (int x = 0; x < levelW; x++) {
            map.push_back(level[y][x]);
        }
    }

    uint32_t W = levelW;
    uint32_t H = levelH;

    std::ofstream ofs("level.bin", std::ios::binary);
    ofs.write((char*)&W, sizeof(W));
    ofs.write((char*)&H, sizeof(H));
    ofs.write((char*)map.data(), sizeof(uint8_t) * H * W);
}

void Level::FileInput() {
    std::ifstream ifs("level.bin", std::ios::binary);
    if (!ifs) return;

    uint32_t W;
    uint32_t H;

    ifs.read(reinterpret_cast<char*>(&W), sizeof(uint32_t));
    ifs.read(reinterpret_cast<char*>(&H), sizeof(uint32_t));
    if (W <= 0 || H <= 0) return;

    levelW = W;
    levelH = H;

    std::vector<uint8_t> map;
    map.resize(W * H);
    
    ifs.read(reinterpret_cast<char*>(map.data()), map.size() * sizeof(uint8_t));

    for (int y = 0; y < (int)H; y++) {
        for (int x = 0; x < (int)W; x++) {
            level[y][x] = map[y * W + x];
        }
    }
}

void Level::Editor() {
    MOUSE mouse = inputP->mouse;
    CAMERA cam = cameraP->GetCam();
    int mouseX = (int)((mouse.x + cam.x - settings::baseW / 2) / blockSize);
    int mouseY = (int)((mouse.y + cam.y - settings::baseH / 2) / blockSize);

    SDL_Color color = { 255,255,255,255 };
    texturesP->DrawTextA(std::to_string(mouseX) + " " + std::to_string(mouseY), color, 1700, 1000, 1, 1);

    if (mouse.right) {
        level[mouseY][mouseX] = 0;
    }
    if (mouse.left) {
        level[mouseY][mouseX] = 1;
    }
}

void Level::DrawMap() {
    for (int y = 0; y < levelH; y++) {
        for (int x = 0; x < levelW; x++) {
            std::string texName = std::to_string(level[y][x]);
            if (texName != "0") {
                OBJRECT rect;
                rect.x = blockSize * x + blockSize / 2;
                rect.y = blockSize * y + blockSize / 2;
                rect.w = blockSize;
                rect.h = blockSize;
                texturesP->DrawImage(texName, rect);
            }
        }
    }
};


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