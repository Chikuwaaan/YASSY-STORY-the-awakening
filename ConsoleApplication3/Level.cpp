#include "Level.h"
#include "Textures.h"
#include "namespace.h"
#include "Input.h"
#include "Camera.h"
#include <cmath>
#include <fstream>
#include <SDL_mixer.h>

Textures* Level::texturesP = nullptr;
Input* Level::inputP = nullptr;
Camera* Level::cameraP = nullptr;
Game* Level::gameP = nullptr;


Level::Level() {
    editorPalette = 1;
    levelW = 256;
    levelH = 32;
    blockSize = 80.0;
    rooms.push_back({ 0,0,{
        {1,1,1,1,1,1,1,1,1,1}
} });

    blockProperty.push_back({});
    blockProperty.push_back({ {1,1,1,1,0,0,0,0},{
        {0b0000, "1-0000"},{0b0001, "1-0001"},{0b0010, "1-0010"},{0b0011, "1-0011"},
        {0b0100, "1-0100"},{0b0101, "1-0101"},{0b0110, "1-0110"},{0b1000, "1-1000"},
        {0b1001, "1-1001"},{0b1010, "1-1010"},{0b1100, "1-1100"},{0b1111, "1-1111"},
        {0b0111, "1-0111"},{0b1110, "1-1110"},{0b1101, "1-1101"},{0b1011, "1-1011"}
} });
    blockProperty.push_back({ {0,1,0,1,0,0,0,0}, {
        {0, "2-0"},{2, "2-2"},{8, "2-8"},{10, "2-10"}
} });
    blockProperty.push_back({ {0,0,0,0,0,0,0,0}, {
        {0, "3-0"}
} });
    blockProperty.push_back({ {1,1,1,1,0,0,0,0},{
        {0b0000, "4-0000"},{0b0001, "4-0001"},{0b0010, "4-0010"},{0b0011, "4-0011"},
        {0b0100, "4-0100"},{0b0101, "4-0101"},{0b0110, "4-0110"},{0b1000, "4-1000"},
        {0b1001, "4-1001"},{0b1010, "4-1010"},{0b1100, "4-1100"},{0b1111, "4-1111"},
        {0b0111, "4-0111"},{0b1110, "4-1110"},{0b1101, "4-1101"},{0b1011, "4-1011"}
} });
}

void Level::FileOutput(int n) {
    std::vector<uint8_t> map;
    map.reserve(levelW * levelH);

    for (int y = 0; y < levelH; y++) {
        for (int x = 0; x < levelW; x++) {
            map.push_back(level[y][x]);
        }
    }

    uint32_t W = levelW;
    uint32_t H = levelH;

    std::string path = "Levels/";
    path = path + std::to_string(n) + "/map.bin";
    std::ofstream ofs(path, std::ios::binary);
    ofs.write((char*)&W, sizeof(W));
    ofs.write((char*)&H, sizeof(H));
    ofs.write((char*)map.data(), sizeof(uint8_t) * H * W);
}


void Level::LoadLevel(int n) {
    LoadMap(n);
}

void Level::LoadMap(int n) {
    std::string path = "Levels/";
    path = path + std::to_string(n) + "/map.bin";
    std::ifstream ifs(path, std::ios::binary);
    if (!ifs) return;

    uint32_t W;
    uint32_t H;
    ifs.read(reinterpret_cast<char*>(&W), sizeof(uint32_t));
    ifs.read(reinterpret_cast<char*>(&H), sizeof(uint32_t));
    if (W <= 0 || H <= 0) return;

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

    SDL_Color color1 = { 255,255,255,255 };
    SDL_Color color2 = { 0,0,0,255 };
    texturesP->DrawImage(blockProperty[editorPalette].tex[0], {1880, 40, 80, 80}, 0 ,{});
    texturesP->DrawTexts(std::to_string(mouseX), color1, color2, { 1400, 0, 1, 1 }, 0, Anchor::Center);
    texturesP->DrawTexts(std::to_string((int)(mouseX * blockSize)), color1, color2, { 1400, 50, 1, 1 }, 0, Anchor::Center);
    texturesP->DrawTexts(std::to_string(mouseY), color1, color2, { 1600, 0, 1, 1 }, 0, Anchor::Center);
    texturesP->DrawTexts(std::to_string((int)(mouseY * blockSize)), color1, color2, { 1600, 50, 1, 1 }, 0, Anchor::Center);
    texturesP->DrawTexts(std::to_string((int)(mouseX * blockSize + blockSize / 2)), color1, color2, { 1400, 100, 1, 1 }, 0, Anchor::Center);
    texturesP->DrawTexts(std::to_string((int)(mouseY * blockSize + blockSize / 2)), color1, color2, { 1600, 100, 1, 1 }, 0, Anchor::Center);

}

void Level::DrawMap() {
    for (int y = 0; y < levelH; y++) {
        for (int x = 0; x < levelW; x++) {

            int blockType = level[y][x];
            if (blockType != 0) {
                int mask = CheckAroundTile(y, x, blockProperty[blockType].checkFor, blockType);
                std::string tex = GetTexName(blockType, mask);
                OBJRECT rect;
                rect.x = blockSize * x + blockSize / 2;
                rect.y = blockSize * y + blockSize / 2;
                rect.w = blockSize;
                rect.h = blockSize;

                if (blockType == 4) {
                    double second = Mix_GetMusicPosition(NULL);
                    if ((int)floor(second * 140 / 60) % 2) {
                        tex = tex + 'a';
                    }
                    else {
                        tex = tex + 'b';
                    }
                }
                texturesP->DrawImage(tex, rect, 1, {});
            }
        }
    }
};

std::string Level::GetTexName(int block, int mask) {
    if (block >= blockProperty.size()) return "missing";

    if (blockProperty[block].tex.count(mask) == 0) {
        return "missing";
    }
    else {
        return blockProperty[block].tex[mask];
    }
}

double Level::GetBlockSize() {
    return blockSize;
}

int Level::CheckAroundTile(int y, int x, CHECKFOR checkFor, int type) {
    int a = 0;
    int X, Y;
    
    X = x + 1;
    if (X < levelW && checkFor.a) {
        a += CheckTile(y, X, type) * 1;
    }
    Y = y + 1;
    if (Y < levelH && checkFor.b) {
        a += CheckTile(Y, x, type) * 2;
    }
    X = x - 1;
    if (X >= 0 && checkFor.c) {
        a += CheckTile(y, X, type) * 4;
    }
    Y = y - 1;
    if (Y >= 0 && checkFor.d) {
        a += CheckTile(Y, x, type) * 8;
    }

    
    X = x + 1;
    Y = y + 1;
    if (X < levelW && Y < levelH && checkFor.e) {
        a += CheckTile(Y, X, type) * 16;
    }
    X = x - 1;
    Y = y + 1;
    if (X >= 0 && Y < levelH && checkFor.f) {
        a += CheckTile(Y, X, type) * 32;
    }
    X = x - 1;
    Y = y - 1;
    if (X >= 0 && Y >= 0 && checkFor.g) {
        a += CheckTile(Y, X, type) * 64;
    }
    X = x + 1;
    Y = y - 1;
    if (X < levelW && Y >= 0 && checkFor.h) {
        a += CheckTile(Y, X, type) * 128;
    }
    

    return a;
}

bool Level::CheckTile(int y, int x, int type) {
    if (level[y][x] == type) {
        return 1;
    }
    else {
        return 0;
    }
}

OBJRECT Level::IsTouching2(OBJRECT obj1, bool direction) {
    SDL_Color color = { 255,255,255,255 };

    int levelX = (int)round((obj1.x - blockSize / 2) / blockSize);
    int extraX = (int)round((obj1.x) / blockSize);
    int levelY = (int)round((obj1.y - blockSize / 2) / blockSize);
    int extraY = (int)round((obj1.y) / blockSize);

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