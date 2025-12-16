#include "Camera.h"
#include "Textures.h"
#include "namespace.h"

Textures* Camera::texturesP = nullptr;

Camera::Camera() {
    camera.x = 960.0;
    camera.y = 540.0;
    camera.offsetX = 0.0;
    camera.offsetY = 0.0;
    camera.targetX = 960.0;
    camera.targetY = 540.0;
    camera.zoom = 1.0;

    //room.push_back({ 0,1920,0,1080,960,960,540,540 });
    //room.push_back({ 1920,1920 * 2,0,1440,960 * 3 - 120,960 * 3 + 120,540,660 });
}

CAMERA Camera::GetCam() {
    return camera;
}

void Camera::SetCam(CAMERA cam) {
    camera = cam;
}

void Camera::SetTargetX(double x) {
    camera.targetX = x;
}

void Camera::SetTargetY(double y) {
    camera.targetY = y;
}

void Camera::Update() {
    //OBJRECT rect = { camera.x,camera.y,60,60 };
    //texturesP->DrawImage("camera", rect);
    texturesP->DrawRect({ 255,255,255,255 }, { camera.x, camera.y, (double)settings::baseW, (double)settings::baseH });

    //camera.x = camera.targetX;
    //camera.y = camera.targetY;
    camera.x = camera.targetX + (camera.x - camera.targetX) / (1.02);
    camera.y = camera.targetY + (camera.y - camera.targetY) / (1.02);


}

std::vector<CAMERAROOM>* Camera::GetRoom() {
    return &room;
}
