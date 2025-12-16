#include "Player.h"
#include "namespace.h"
#include "Level.h"
#include "Camera.h"
#include <iostream>
#include "Textures.h"

Level* Player::levelP = nullptr;
Camera* Player::cameraP = nullptr;

Player::Player(std::string tex) {
    texName = "missing";
    maxSpeed = 480.0;
    minSpeed = 8.0;
    deceleration = 1920.0;
    moveBody = 0;
    x = 180.0;
    y = 1000.0;
    w = 60.0;
    h = 100.0;
    aX = 0.0;
    aY = 0.0;
    flipX = false;
}

void Player::SetAX(double acceleration) {
    aX += acceleration;
}

OBJRECT Player::isTouchingMap(double x, double y, double w, double h) {
    OBJRECT obj = { x, y, w, h };
    return levelP->IsTouching(obj);
}


void Player::Update() {
    cameraP->SetTargetX(x);
    cameraP->SetTargetY(y);
    MoveCameraRoom();


    OBJRECT touchingMap;
    //Y
    vY -= 2000 * settings::timeScale;
    MoveY();
    onGround = false;
    touchingMap = isTouchingMap(x, y, w, h);
    while (touchingMap.touch && vY < 0.0) {
        onGround = true;
        vY = 0.0;
        y = touchingMap.y + 0.5 * h + levelP->GetBlockSize() * 0.5;
        touchingMap = isTouchingMap(x, y, w, h);
    }
    while (touchingMap.touch && vY > 0.0) {
        vY = 0.0;
        y = touchingMap.y - 0.5 * h - levelP->GetBlockSize() * 0.5;
        touchingMap = isTouchingMap(x, y, w, h);
    }

    //X
    vX += aX * settings::timeScale;
    if (vX > maxSpeed) {
        vX = maxSpeed;
    }
    else if (vX < -1 * maxSpeed) {
        vX = -1 * maxSpeed;
    }
    MoveX();
    touchingMap = isTouchingMap(x, y, w, h);
    while (touchingMap.touch) {
        if (vX > 0.0) {
            vX = 0.0;
            x = touchingMap.x - 0.5 * w - levelP->GetBlockSize() * 0.5;
            touchingMap = isTouchingMap(x, y, w, h);
        }
        else if (vX < 0.0) {
            vX = 0.0;
            x = touchingMap.x + 0.5 * w + levelP->GetBlockSize() * 0.5;
            touchingMap = isTouchingMap(x, y, w, h);
        }
        else {
            break;
        }
    }

    if (vX >= minSpeed) {
        vX -= deceleration * settings::timeScale;
    }
    else if (vX < minSpeed && vX > minSpeed * -1) {
        vX = 0.0;
    }
    else if (vX <= minSpeed * -1) {
        vX += deceleration * settings::timeScale;
    }
    else {
        vX = 0.0;
    }
    aX = 0.0;

    if (y < -1000.0) {
        x = 180.0;
        y = 180.0;
        w = 60.0;
        h = 100.0;
        //Mix_Music* music = Mix_LoadMUS("Assets/audio/sanctuary.wav");
        //Mix_PlayMusic(music, -1);
    }

    if (!onGround) {
        moveBody += 12 * settings::timeScale;
    }

    if (vX != 0.0) {
        moveBody += 12 * settings::timeScale;
    }
    else if (onGround) {
        moveBody = 0;
    }

    
}

void Player::Jump() {
    if (onGround) {
        vY = 1250.0;
    }
}

void Player::MoveCameraRoom() {
    std::vector<CAMERAROOM>* room = cameraP->GetRoom();
    CAMERA camera = cameraP->GetCam();


    for (int i = 0; i < room->size(); i++) {
        if (x > (*room)[i].x1 && x < (*room)[i].x2 && y >(*room)[i].y1 && y < (*room)[i].y2) {
            if ((*room)[i].x3 > camera.targetX) {
                camera.targetX = (*room)[i].x3;
            }
            else
                if ((*room)[i].x4 < camera.targetX) {
                    camera.targetX = (*room)[i].x4;
                }
            if ((*room)[i].y3 > camera.targetY) {
                camera.targetY = (*room)[i].y3;
            }
            else
                if ((*room)[i].y4 < camera.targetY) {
                    camera.targetY = (*room)[i].y4;
                }
        }
    }
    cameraP->SetCam(camera);
}

void Player::DrawPlayer() {
    DrawPart("legL", sin(moveBody) * 16, 30, 60);
    DrawPart("legR", sin(moveBody) * -16, 34, 60);
    DrawPart("body", sin(moveBody), 0, 0);
    DrawPart("head", sin(moveBody) * 4, 80, 20);
    DrawPart("armL", sin(moveBody) * -16, 90, 60);
    DrawPart("armR", sin(moveBody) * 16, 70, 70);
}

void Player::DrawPart(std::string tex, double angle, int X, int Y) {
    OBJRECT rect;
    rect.x = (int)x + 20 + flipX * -40;
    rect.y = (int)y + 4;
    rect.w = 140;
    rect.h = 140;
    OBJRECT point;
    if (flipX) {
        point.x = 140 - X;
    }
    else {
        point.x = X;
    }
    point.y = Y;
    texturesP->DrawImageEx(tex, rect, angle, point, flipX, 0);
}