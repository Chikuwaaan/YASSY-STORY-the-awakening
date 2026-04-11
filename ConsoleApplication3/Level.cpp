#include "Level.h"
#include "Textures.h"
#include "Sounds.h"
#include "namespace.h"
#include "Input.h"
#include "Camera.h"
#include "Player.h"
#include <cmath>
#include <fstream>
#include <SDL_mixer.h>

Textures* Level::texturesP = nullptr;
Sounds* Level::soundsP = nullptr;
Input* Level::inputP = nullptr;
Camera* Level::cameraP = nullptr;
Game* Level::gameP = nullptr;
Player* Level::playerP = nullptr;

Level::Level() :
    level{ {} }
{
    levelW = 1024;
    levelH = 128;
    blockSize = 96.0;
    dev = 0;
    editorPalette = 1;
    mouseX = 0;
    mouseY = 0;
    mouseXC = 0;
    mouseYC = 0;

    rooms.push_back({ 0,0,{
        {1,1,1,1,1,1,1,1,1,1}
} });

    blockProperty.push_back({
        "null",
        0,
        {0,0,blockSize,blockSize},
        0,
        });
    blockProperty.push_back({
        "block1",
        1,
        {0,0,blockSize,blockSize},
        0
        });
    blockProperty.push_back({
        "block2",
        1,
        {0,6 * blockSize / (-16),10 * blockSize / 16,blockSize / 4},
        1
        });
    blockProperty.push_back({
        "block3",
        1,
        {6 * blockSize / 16, 0, blockSize / 4, 10 * blockSize / 16,},
        1
        });
    blockProperty.push_back({
        "block4",
        1,
        {0,6 * blockSize / 16,10 * blockSize / 16,blockSize / 4},
        1
        });
    blockProperty.push_back({
        "block5",
        1,
        {6 * blockSize / (-16), 0, blockSize / 4, 10 * blockSize / 16,},
        1
        });
    blockProperty.push_back({
        "block6",
        2,
        {0,0,blockSize,blockSize},
        0
        });
    blockProperty.push_back({
        "block7",
        2,
        {0,0,0,0},
        0
        });
    blockProperty.push_back({
        "block8",
        1,
        {0,0,blockSize,blockSize},
        2
        });
    blockProperty.push_back({
        "block9b",
        1,
        {0,0,blockSize,blockSize},
        0
        });
    blockProperty.push_back({
        "block10",
        1,
        {0,0,blockSize,blockSize},
        0,
        1
        });
    blockProperty.push_back({
        "block11",
        3,
        {0,0,blockSize,blockSize},
        0
        });
    blockProperty.push_back({
        "block12",
        1,
        {0,0,blockSize,blockSize},
        0
        });
    blockProperty.push_back({
        "block13",
        1,
        {0,0,blockSize,blockSize},
        0,
        0,
        1
        });
    blockProperty.push_back({
        "block14",
        1,
        {0,0,blockSize,blockSize},
        0,
        0,
        0,
        140
        });
    blockProperty.push_back({
        "block15",
        1,
        {0,0,blockSize,blockSize},
        0,
        0,
        0,
        2400,
        480
        });
    blockProperty.push_back({
        "block16",
        1,
        {0,0,blockSize,blockSize},
        0,
        0,
        0,
        2400,
        -480
        });
    /*
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
    blockProperty.push_back({ {0,0,0,0,0,0,0,0},{
        {0b0000, "5-0000"}
} });
*/
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

void Level::Update() {
    MOUSE mouse = inputP->mouse;
    CAMERA camera = cameraP->GetCam();

    int pivotX = settings::baseW / 2;
    int pivotY = settings::baseH / 2;
    mouseX = (int)((mouse.x / camera.zoom + (camera.x - pivotX + camera.offsetX + settings::baseW * (0.5 - 0.5 / camera.zoom))) / blockSize);
    mouseY = (int)((mouse.y / camera.zoom + (camera.y - pivotY + camera.offsetY + settings::baseH * (0.5 - 0.5 / camera.zoom))) / blockSize);
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

    mouseXC = mouseX * (int)blockSize + (int)blockSize / 2;
    mouseYC = mouseY * (int)blockSize + (int)blockSize / 2;
}

void Level::Editor() {
    MOUSE mouse = inputP->mouse;
    EVENT event = inputP->event;

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
    texturesP->DrawSprite(blockProperty[editorPalette].tex, { 1920 - 48, 1080 - 48, blockSize, blockSize }, { 0,0,16,16 }, 0);

    std::string blockIndex = std::to_string(mouseX) + "," + std::to_string(mouseY);
    std::string blockPos = std::to_string(mouseX * (int)blockSize) + ',' + std::to_string(mouseY * (int)blockSize);
    std::string blockCenter = std::to_string((int)mouseXC) + "," + std::to_string((int)mouseYC);
    texturesP->DrawTexts(blockIndex, color1, color2, { 1400, 1030, 1, 1 }, 0, Anchor::Left);
    texturesP->DrawTexts(blockPos, color1, color2, { 1400, 980, 1, 1 }, 0, Anchor::Left);
    texturesP->DrawTexts(blockCenter, color1, color2, { 1400, 930, 1, 1 }, 0, Anchor::Left);

    if (event.F2) {
        std::cout << blockIndex << std::endl;
    }
    if (event.F3) {
        std::cout << blockPos << std::endl;
    }
    if (event.F4) {
        std::cout << blockCenter << std::endl;
    }

}

void Level::DrawMap(bool mode) {
    for (int y = 0; y < levelH; y++) {
        for (int x = 0; x < levelW; x++) {
            int blockType = level[y][x];

            if (!mode) {
                if (blockProperty[blockType].invisible) {
                    OBJRECT rectP = playerP->GetRect();
                    double distance = utilities::DistanceSQ(
                        blockSize * x + blockSize * 0.5,
                        blockSize * y + blockSize * 0.5,
                        rectP.x,
                        rectP.y
                    );
                    if (distance > 160000) continue;

                }
            }


            if (blockProperty[blockType].renderingType == 1) {
                std::string tex = blockProperty[blockType].tex;

                OBJRECT rect1;
                rect1.x = blockSize * x + blockSize * 0.75;
                rect1.y = blockSize * y + blockSize * 0.75;
                rect1.w = blockSize / 2;
                rect1.h = blockSize / 2;
                SDL_Rect src1 = CheckAroundTile1(y, x, CHECKFOR::TopRight, blockType);
                texturesP->DrawSprite(tex, rect1, src1, 1);

                OBJRECT rect2;
                rect2.x = blockSize * x + blockSize * 0.25;
                rect2.y = blockSize * y + blockSize * 0.75;
                rect2.w = blockSize / 2;
                rect2.h = blockSize / 2;
                SDL_Rect src2 = CheckAroundTile1(y, x, CHECKFOR::TopLeft, blockType);
                texturesP->DrawSprite(tex, rect2, src2, 1);

                OBJRECT rect3;
                rect3.x = blockSize * x + blockSize * 0.25;
                rect3.y = blockSize * y + blockSize * 0.25;
                rect3.w = blockSize / 2;
                rect3.h = blockSize / 2;
                SDL_Rect src3 = CheckAroundTile1(y, x, CHECKFOR::BottomLeft, blockType);
                texturesP->DrawSprite(tex, rect3, src3, 1);

                OBJRECT rect4;
                rect4.x = blockSize * x + blockSize * 0.75;
                rect4.y = blockSize * y + blockSize * 0.25;
                rect4.w = blockSize / 2;
                rect4.h = blockSize / 2;
                SDL_Rect src4 = CheckAroundTile1(y, x, CHECKFOR::BottomRight, blockType);
                texturesP->DrawSprite(tex, rect4, src4, 1);

                if (dev) {
                    OBJRECT rect;
                    rect.x = blockSize * x + blockSize / 2 + blockProperty[blockType].hitBox.x;
                    rect.y = blockSize * y + blockSize / 2 + blockProperty[blockType].hitBox.y;
                    rect.w = blockProperty[blockType].hitBox.w;
                    rect.h = blockProperty[blockType].hitBox.h;
                    texturesP->DrawRect({ 0,0,255,255 }, rect, 1);
                }

            }
            else if (blockProperty[blockType].renderingType == 2) {
                OBJRECT rect;
                rect.x = blockSize * x + blockSize / 2 + blockProperty[blockType].hitBox.x;
                rect.y = blockSize * y + blockSize / 2 + blockProperty[blockType].hitBox.y;
                rect.w = blockSize;
                rect.h = blockSize;

                std::string tex = blockProperty[blockType].tex;
                SDL_Rect src = CheckAroundTile2(y, x, blockType);
                texturesP->DrawSprite(tex, rect, src, 1);
            }
            else if (blockProperty[blockType].renderingType == 3) {
                OBJRECT rect;
                rect.x = blockSize * x + blockSize / 2 + blockProperty[blockType].hitBox.x;
                rect.y = blockSize * y + blockSize / 2 + blockProperty[blockType].hitBox.y;
                rect.w = blockSize;
                rect.h = blockSize;

                std::string tex = blockProperty[blockType].tex;
                SDL_Rect src = CheckAroundTile3(y, x, blockType);
                texturesP->DrawSprite(tex, rect, src, 1);
            }
        }
    }
};

double Level::GetBlockSize() {
    return blockSize;
}

SDL_Rect Level::CheckAroundTile1(int y, int x, CHECKFOR checkFor, int type) {
    int size = 8;
    SDL_Rect src = { 0,0,size,size };
    bool yoko = 0, tate = 0, naname = 0;

    if (checkFor == CHECKFOR::TopRight) {
        src = { size,0,size,size };
        if (x < levelW - 1) {
            if (level[y][x + 1] == type) {
                yoko = 1;
            }
        }
        if (y < levelH - 1) {
            if (level[y + 1][x] == type) {
                tate = 1;
            }
        }
        if (x < levelW - 1 && y < levelH - 1) {
            if (level[y + 1][x + 1] == type) {
                naname = 1;
            }
        }
    }
    if (checkFor == CHECKFOR::TopLeft) {
        src = { 0,0,size,size };
        if (x > 0) {
            if (level[y][x - 1] == type) {
                yoko = 1;
            }
        }
        if (y < levelH - 1) {
            if (level[y + 1][x] == type) {
                tate = 1;
            }
        }
        if (x > 0 && y < levelH - 1) {
            if (level[y + 1][x - 1] == type) {
                naname = 1;
            }
        }
    }
    if (checkFor == CHECKFOR::BottomLeft) {
        src = { 0,size,size,size };
        if (x > 0) {
            if (level[y][x - 1] == type) {
                yoko = 1;
            }
        }
        if (y > 0) {
            if (level[y - 1][x] == type) {
                tate = 1;
            }
        }
        if (x > 0 && y > 0) {
            if (level[y - 1][x - 1] == type) {
                naname = 1;
            }
        }
    }
    if (checkFor == CHECKFOR::BottomRight) {
        src = { size,size,size,size };
        if (x < levelW - 1) {
            if (level[y][x + 1] == type) {
                yoko = 1;
            }
        }
        if (y > 0) {
            if (level[y - 1][x] == type) {
                tate = 1;
            }
        }
        if (x < levelW - 1 && y > 0) {
            if (level[y - 1][x + 1] == type) {
                naname = 1;
            }
        }
    }

    if (blockProperty[type].bpm != 0) {
        if ((int)(soundsP->GetMusicPosition() * blockProperty[type].bpm / 60) % 2) {
            src.y += 16;
        }
        
    }
    

    if (yoko && tate && naname) {
        src.x += size * 8;
        return src;
    }
    if (yoko && !tate) {
        src.x += size * 2;
        return src;
    }
    if (!yoko && tate) {
        src.x += size * 4;
        return src;
    }
    if (yoko && tate) {
        src.x += size * 6;
        return src;
    }
    
    return src;
}

SDL_Rect Level::CheckAroundTile2(int y, int x, int type) {
    int size = 16;
    SDL_Rect src = { 0,0,size,size };
    bool yoko = 0, tate = 0;

    if (x > 0 && x < levelW - 1) {
        if (level[y][x - 1] == type || type == level[y][x + 1]) {
            yoko = 1;
        }
    }
    if (y > 0 && y < levelH - 1) {
        if (level[y - 1][x] == type || type == level[y + 1][x]) {
            tate = 1;
        }
    }


    if (yoko) {
        src.x = size;
        return src;
    }if (tate) {
        src.x = size * 2;
        return src;
    }
    return src;
}

SDL_Rect Level::CheckAroundTile3(int y, int x, int type) {
    int size = 16;
    SDL_Rect src = { 0,0,size,size };
    bool yoko = 0, tate = 0;

    if (x > 0 && x < levelW - 1) {
        if (level[y][x - 1] == type || type == level[y][x + 1]) {
            yoko = 1;
        }
    }
    if (y > 0 && y < levelH - 1) {
        if (level[y - 1][x] == type || type == level[y + 1][x]) {
            tate = 1;
        }
    }

    if (tate) {
        src.x = size * 2;
        return src;
    }
    if (yoko) {
        src.x = size;
        return src;
    }
    return src;
}


OBJRECT Level::IsTouching2(OBJRECT obj1, bool direction) {
    SDL_Color color = { 255,255,255,255 };

    int levelX = (int)round((obj1.x - blockSize / 2) / blockSize);
    int extraX;
    if ((obj1.x - blockSize / 2.0) / blockSize > levelX) {
        extraX = levelX + 1;
    }
    else {
        extraX = levelX - 1;
    }

    int levelY = (int)round((obj1.y - blockSize / 2) / blockSize);
    int extraY;
    if ((obj1.y - blockSize / 2) / blockSize > levelY) {
        extraY = levelY + 1;
    }
    else {
        extraY = levelY - 1;
    }

    //0=y, 1=x
    if (!direction) {
        for (int i = -1; i < 2; i += 1) {
            int blockX = levelX;
            int blockY = levelY + i;
            FixBlockPos(&blockX, &blockY);
            int blockType = level[blockY][blockX];

            //真ん中
            if (blockType) {
                OBJRECT obj2;
                obj2.x = (blockX + 0.5) * blockSize + blockProperty[blockType].hitBox.x;
                obj2.y = (blockY + 0.5) * blockSize + blockProperty[blockType].hitBox.y;
                obj2.w = blockProperty[blockType].hitBox.w;
                obj2.h = blockProperty[blockType].hitBox.h;
                obj2.block = blockType;
                if (utilities::HitDetection(obj1, obj2)) {
                    if (dev) texturesP->DrawRect({ 0,255,0,63 }, obj2, 1);
                    return obj2;
                }
            }

            //端っこ
            blockX = extraX;
            FixBlockPos(&blockX, &blockY);
            blockType = level[blockY][blockX];
            if (blockType) {
                OBJRECT obj2;
                obj2.x = (blockX + 0.5) * blockSize + blockProperty[blockType].hitBox.x;
                obj2.y = (blockY + 0.5) * blockSize + blockProperty[blockType].hitBox.y;
                obj2.w = blockProperty[blockType].hitBox.w;
                obj2.h = blockProperty[blockType].hitBox.h;
                obj2.block = blockType;
                if (utilities::HitDetection(obj1, obj2)) {
                    if (dev) texturesP->DrawRect({ 0,255,0,63 }, obj2, 1);
                    return obj2;
                }
            }
        }
    }

    else {
        for (int i = -1; i < 2; i += 1) {
            int blockX = levelX + i;
            int blockY = levelY;
            FixBlockPos(&blockX, &blockY);
            int blockType = level[blockY][blockX];

            //真ん中
            if (blockType) {
                OBJRECT obj2;
                obj2.x = (blockX + 0.5) * blockSize + blockProperty[blockType].hitBox.x;
                obj2.y = (blockY + 0.5) * blockSize + blockProperty[blockType].hitBox.y;
                obj2.w = blockProperty[blockType].hitBox.w;
                obj2.h = blockProperty[blockType].hitBox.h;
                obj2.block = blockType;
                if (utilities::HitDetection(obj1, obj2)) {
                    if (dev) texturesP->DrawRect({ 0,255,0,63 }, obj2, 1);
                    return obj2;
                }
            }

            //端っこ
            blockY = extraY;
            FixBlockPos(&blockX, &blockY);
            blockType = level[blockY][blockX];
            if (blockType) {
                OBJRECT obj2;
                obj2.x = (blockX + 0.5) * blockSize + blockProperty[blockType].hitBox.x;
                obj2.y = (blockY + 0.5) * blockSize + blockProperty[blockType].hitBox.y;
                obj2.w = blockProperty[blockType].hitBox.w;
                obj2.h = blockProperty[blockType].hitBox.h;
                obj2.block = blockType;
                if (utilities::HitDetection(obj1, obj2)) {
                    if (dev) texturesP->DrawRect({ 0,255,0,63 }, obj2, 1);
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

void Level::GetMouseC(double* x, double* y) {
    *x = mouseXC;
    *y = mouseYC;
}