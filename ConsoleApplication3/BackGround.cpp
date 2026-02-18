#include "BackGround.h"
#include "Textures.h"
#include "Camera.h"

BackGround::BackGround() {
}

void BackGround::Draw() {
    CAMERA cam = cameraP->GetCam();

    OBJRECT rect;
    rect.x = settings::baseW / 2 + ((cam.x - settings::baseW / 2) * 0.9);
    rect.y = settings::baseH / 2 + ((cam.y - settings::baseH / 2) * 0.9);
    rect.w = settings::baseW * 2;
    rect.h = settings::baseH * 2;
    texturesP->DrawImage("bg1", rect, 1, {});
    /*
    CAMERA cam = cameraP->GetCam();
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            int bgx = j;
            int bgy = i;
            OBJRECT rect;
            rect.x = ((cam.x - settings::baseW / 2) * 0.8) + (settings::baseW * (bgx + 0.5));
            rect.y = ((cam.y - settings::baseH / 2) * 0.8) + (settings::baseH * (bgy + 0.5));
            rect.w = settings::baseW * 4;
            rect.h = settings::baseH * 4;

            std::string tex;
            if (i % 2) {
                tex = "bg_0-1";
            }
            else {
                tex = "bg_0-0";
            }
            texturesP->DrawImage(tex, rect, 1, {});
        }
    }
    */
    return;
}