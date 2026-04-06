#include "Camera.h"
#include "Textures.h"
#include "namespace.h"
#include "Input.h"
#include <iostream>
#include <cmath>
#include <fstream>

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
    camera.angle = 30;
    drawCameraRoom = 0;
}

void Camera::Init() {
    camera.x = 720.0;
    camera.y = 540.0;
    camera.offsetX = 0.0;
    camera.offsetY = 0.0;
    camera.targetX = 720.0;
    camera.targetY = 540.0;
    camera.zoom = 1.0;
    drawCameraRoom = 1;
}

void Camera::LoadCameraRoom(int n) {
    room.clear();
    std::string path = "Levels/";
    path = path + std::to_string(n) + "/camera.csv";
    std::ifstream file(path);
    std::string line;

    int i = 0;
    while (std::getline(file, line)) {
        room.push_back({});
        std::stringstream stream(line);
        std::string cell;
        std::getline(stream, cell, ','); room[i].x1 = std::stoi(cell);
        std::getline(stream, cell, ','); room[i].x2 = std::stoi(cell);
        std::getline(stream, cell, ','); room[i].y1 = std::stoi(cell);
        std::getline(stream, cell, ','); room[i].y2 = std::stoi(cell);
        std::getline(stream, cell, ','); room[i].x3 = std::stoi(cell) + settings::baseW / 2;
        std::getline(stream, cell, ','); room[i].x4 = std::stoi(cell) - settings::baseW / 2;
        std::getline(stream, cell, ','); room[i].y3 = std::stoi(cell) + settings::baseH / 2;
        std::getline(stream, cell, ','); room[i].y4 = std::stoi(cell) - settings::baseH / 2;
        std::getline(stream, cell, ','); room[i].force = std::stoi(cell);
        i++;
    }
    
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
        camera.offsetY += 4 / camera.zoom;
    }
    if (keystate[SDL_SCANCODE_DOWN]) {
        camera.offsetY -= 4 / camera.zoom;
    }
    if (keystate[SDL_SCANCODE_LEFT]) {
        camera.offsetX -= 4 / camera.zoom;
    }
    if (keystate[SDL_SCANCODE_RIGHT]) {
        camera.offsetX += 4 / camera.zoom;
    }
    if (inputP->event.MouseWheel) {
        camera.zoom += inputP->event.MouseWheel * 0.1;
        if (camera.zoom < 0.1) {
            camera.zoom = 0.1;
        }
    }
    if (inputP->event.C) {
        camera.offsetX = 0;
        camera.offsetY = 0;
    }

    camera.x = camera.x + (camera.targetX - camera.x) * settings::timeScale * 8;
    camera.y = camera.y + (camera.targetY - camera.y) * settings::timeScale * 4;
    
}

void Camera::Draw() {
    std::string text = std::to_string(camera.x) + ',' + std::to_string(camera.y);
    texturesP->DrawTexts(text, { 255,255,255,255 }, { 0,0,0,255 }, { 50,50,1,1 }, 0, Anchor::Left);

    texturesP->DrawRect({ 0,0,255,255 }, { camera.x, camera.y, (double)settings::baseW, (double)settings::baseH }, 1);
    if (drawCameraRoom) {
        for (int i = 0; i < room.size(); i++) {
            OBJRECT rect;
            rect.x = (room[i].x1 + room[i].x2) / 2;
            rect.y = (room[i].y1 + room[i].y2) / 2;
            rect.w = abs(room[i].x1 - room[i].x2);
            rect.h = abs(room[i].y1 - room[i].y2);
            texturesP->DrawRect({ 255,0,0,255 }, rect, 1);
            texturesP->DrawTexts(std::to_string(i+1), { 255,0,0,255 }, { 255,255,255,255 }, { room[i].x1, room[i].y1,2,2 }, 1, Anchor::Center);

            rect.x = (room[i].x3 + room[i].x4) / 2;
            rect.y = (room[i].y3 + room[i].y4) / 2;
            rect.w = abs(room[i].x3 - room[i].x4);
            rect.h = abs(room[i].y3 - room[i].y4);
            texturesP->DrawRect({ 0,127,0,255 }, rect, 1);
            texturesP->DrawTexts(std::to_string(i+1), { 0,127,0,255 }, { 255,255,255,255 }, { room[i].x3, room[i].y3,2,2 }, 1, Anchor::Center);
        }
    }
}

std::vector<CAMERAROOM>* Camera::GetRoom() {
    return &room;
}
