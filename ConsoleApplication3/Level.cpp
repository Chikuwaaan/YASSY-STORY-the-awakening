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
    editorPalette = 1;
    levelW = 128;
    levelH = 32;
    blockSize = 80.0;
    rooms.push_back({ 0,0,{
        {1,1,1,1,1,1,1,1,1,1}
} });

    blockProperty = {
        {"0_a","0_a","0_a","0_a","0_a","0_a","0_a","0_a","0_a","0_a","0_a","0_a","0_a","0_a","0_a","0_a"},
        {"1-0","1-1","1-2","1-0","1-4","1-5","1-0","1-0","1-8","1-0","1-10","1-0","1-0","1-0","1-0","1-15"}
    };
    

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
    EVENT event = inputP->event;
    CAMERA camera = cameraP->GetCam();
    //int mouseX = (int)((mouse.x + cam.x - settings::baseW / 2 ) / blockSize);

    int pivotX = settings::baseW / 2;
    int pivotY = settings::baseH / 2;
    int mouseX = (int)((mouse.x / camera.zoom + (camera.x - pivotX + camera.offsetX + settings::baseW * (0.5 - 0.5 / camera.zoom))) / blockSize);
    int mouseY = (int)((mouse.y / camera.zoom + (camera.y - pivotY + camera.offsetY + settings::baseH * (0.5 - 0.5 / camera.zoom))) / blockSize);
    if (mouseX < 0) {
        mouseX = 0;
    }
    else if (mouseX >= levelW) {
        mouseX = levelW - 1;
    }
    if (mouseY < 0) {
        mouseY = 0;
    }
    else if (mouseY >= levelH) {
        mouseY = levelH - 1;
    }
    SDL_Color color = { 255,255,255,255 };
    texturesP->DrawTextA(std::to_string(mouseX) + " " + std::to_string(mouseY), color, 1700, 1000, 1, 1);
    
    

    if (event.MouseX1) {
        if (editorPalette > 0) editorPalette--;
    }
    if (event.MouseX2) {
        if (editorPalette < blockProperty.size() - 1) editorPalette++;
    }

    if (mouse.right) {
        level[mouseY][mouseX] = 0;
    }
    if (mouse.left) {
        level[mouseY][mouseX] = editorPalette;
    }

    texturesP->DrawImageA(blockProperty[editorPalette][0], {1830, 10, 80, 80});
    texturesP->DrawTextA(std::to_string(editorPalette), {255,255,255,255}, 1830, 100, 1, 1);
}

void Level::DrawMap() {
    for (int y = 0; y < levelH; y++) {
        for (int x = 0; x < levelW; x++) {
            if (level[y][x] != 0) {
                int mask = CheckAroundTile(y, x);
                std::string tex = blockProperty[level[y][x]][mask];
                OBJRECT rect;
                rect.x = blockSize * x + blockSize / 2;
                rect.y = blockSize * y + blockSize / 2;
                rect.w = blockSize;
                rect.h = blockSize;
                texturesP->DrawImage(tex, rect);
            }
        }
    }
};

int Level::CheckAroundTile(int y, int x) {
    int a = 0;
    int X, Y;
    
    X = x + 1;
    if (X < levelW) {
        a += CheckTile(y, X) * 1;
    }
    X = x - 1;
    if (X >= 0) {
        a += CheckTile(y, X) * 4;
    }

    Y = y + 1;
    if (Y < levelH) {
        a += CheckTile(Y, x) * 2;
    }
    Y = y - 1;
    if (Y >= 0) {
        a += CheckTile(Y, x) * 8;
    }

    return a;
}

bool Level::CheckTile(int y, int x) {
    if (level[y][x] == 0) {
        return 0;
    }
    else {
        return 1;
    }
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