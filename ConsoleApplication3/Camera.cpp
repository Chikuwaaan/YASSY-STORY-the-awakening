#include "Camera.h"
#include "Textures.h"
#include "namespace.h"
#include "Input.h"
#include <iostream>

Textures* Camera::texturesP = nullptr;
Input* Camera::inputP = nullptr;

Camera::Camera() {
    camera.x = 720.0;
    camera.y = 540.0;
    camera.offsetX = 0.0;
    camera.offsetY = 0.0;
    camera.targetX = 720.0;
    camera.targetY = 540.0;
    camera.zoom = 1.0;

    //room.push_back({ 0,1920,0,1080,960,960,540,540 });
    //room.push_back({ 1920,1920 * 2,0,1440,960 * 3 - 120,960 * 3 + 120,540,660 });
    //room.push_back({ 0,1440,0,1080,720,720,540,540 });
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
    const Uint8* keystate = inputP->keystate;

    if (keystate[SDL_SCANCODE_UP]) {
        camera.offsetY += 4;
    }
    if (keystate[SDL_SCANCODE_DOWN]) {
        camera.offsetY -= 4;
    }
    if (keystate[SDL_SCANCODE_LEFT]) {
        camera.offsetX -= 4;
    }
    if (keystate[SDL_SCANCODE_RIGHT]) {
        camera.offsetX += 4;
    }
    if (inputP->event.mouseWheel != 0) {
        camera.zoom += inputP->event.mouseWheel * 0.1;
    }

    texturesP->DrawRect({ 255,255,255,255 }, { camera.x, camera.y, (double)settings::baseW, (double)settings::baseH });

    camera.x = camera.targetX + (camera.x - camera.targetX) / (1.02);
    camera.y = camera.targetY + (camera.y - camera.targetY) / (1.02);


}

std::vector<CAMERAROOM>* Camera::GetRoom() {
    return &room;
}
