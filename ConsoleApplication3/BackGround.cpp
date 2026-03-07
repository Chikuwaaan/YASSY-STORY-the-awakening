#include "BackGround.h"
#include "Textures.h"
#include "Camera.h"

BackGround::BackGround(double X, double Y, double size, double mul, double camX, double camY, double Layer, std::string tex) {
    x0 = X + settings::baseW / 2 * size;
    y0 = Y + settings::baseH / 2 * size;
    dx = 0;
    dy = 0;
    camX0 = camX;
    camY0 = camY;
    M = mul;
    texName = tex;
    type = EntityType::BackGround;
    alwaysLoad = 1;
    layer = (int)Layer;

    w = settings::baseW * size;
    h = settings::baseH * size;
}

void BackGround::Draw() {
    
    texturesP->DrawImage(texName, {x,y,w,h}, 1, {});
    return;
}

void BackGround::Update() {
    bool isCloud = 0;
    if (texName == "cloud1") {
        dx = timer.GetTime() * -30;
        isCloud = 1;
    }
    if (texName == "cloud2") {
        dx = timer.GetTime() * -60;
        isCloud = 1;
    }
    if (texName == "cloud3") {
        dx = timer.GetTime() * -90;
        isCloud = 1;
    }
    if (1) {
        if (dx < (settings::baseW * -1)) {
            timer.Reset();
        }
    }

    CAMERA cam = cameraP->GetCam();
    x = x0 + dx + (cam.x - camX0) * M;
    y = y0 + dy +(cam.y - camY0) * M;
    
}