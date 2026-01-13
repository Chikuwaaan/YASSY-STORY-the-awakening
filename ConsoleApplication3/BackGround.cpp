#include "BackGround.h"
#include "Textures.h"
#include "Camera.h"

BackGround::BackGround() {
}

void BackGround::Draw() {
    CAMERA cam = cameraP->GetCam();
    OBJRECT rect = { cam.x*0.8,cam.y*0.8,(double)settings::baseW*4,(double)settings::baseH*4 };
    texturesP->DrawImage("bg_0", rect, 1, {});
}