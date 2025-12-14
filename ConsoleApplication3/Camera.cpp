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
}

CAMERA Camera::getCam() {
    return camera;
}

void Camera::setCam(CAMERA cam) {
    camera = cam;
}

void Camera::Update() {
    OBJRECT rect = { camera.x,camera.y,60,60 };
    texturesP->DrawImage("camera", rect);
    texturesP->DrawRect({ 255,255,255,255 }, { camera.x, camera.y, (double)settings::baseW, (double)settings::baseH });
}