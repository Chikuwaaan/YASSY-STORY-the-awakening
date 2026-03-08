#include "BackGround.h"
#include "Textures.h"
#include "Camera.h"

BackGround::BackGround(double X, double Y, double mulX, double mulY, double camX, double camY, double Layer, std::string tex) {
    int W = 0, H = 0;
    SDL_QueryTexture(texturesP->GetTexture(tex), NULL, NULL, &W, &H);
    w = W * 6;
    h = H * 6;
    
    x0 = X + w / 2;
    y0 = Y + h / 2;
    dx = 0;
    dy = 0;
    camX0 = camX;
    camY0 = camY;
    Mx = mulX;
    My = mulY;
    texName = tex;
    type = EntityType::BackGround;
    alwaysLoad = 1;
    layer = (int)Layer;
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
    x = x0 + dx + (cam.x - camX0) * Mx;
    y = y0 + dy +(cam.y - camY0) * My;
    
}