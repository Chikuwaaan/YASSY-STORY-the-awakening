#include "Player.h"
#include "namespace.h"
#include "Level.h"
#include "Camera.h"
#include <iostream>
#include <SDL_mixer.h>
#include "Textures.h"
#include "Input.h"

Level* Player::levelP = nullptr;
Camera* Player::cameraP = nullptr;

Player::Player() {
    texName = "assy";
    maxSpeed = 480.0;
    minSpeed = 8.0;
    deceleration = 1920.0;
    moveBody = 0;
    x = 180.0;
    y = 1000.0;
    w = 60.0;
    h = 80.0;
    aX = 0.0;
    aY = 0.0;
    flipX = false;
    coyoteTime = 0;
    walkVX = 0.0;
    liftVX = 0.0;
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

    const Uint8* keystate = inputP->keystate;
    if (keystate[SDL_SCANCODE_W]) {
        Jump();
    }
    if (keystate[SDL_SCANCODE_A]) {
        SetAX(-3840.0);
        FlipX(true);
    }
    if (keystate[SDL_SCANCODE_D]) {
        SetAX(3840.0);
        FlipX(false);
    }
    

    //Y
    vY += platformer::gravity * settings::timeScale;
    MoveY();
    CollideY();

    liftVX = 0.0;
    if (groundBlock == 2) {
        Jump();
    }
    else if (headBlock == 2) {
        vY = -1000.0;
    }
    else if (headBlock == 3) {
        Die();
    }
    else if (groundBlock == 4) {
        liftVX = -360;
    }


    //X
    walkVX += aX * settings::timeScale;
    if (walkVX > maxSpeed) {
        walkVX = maxSpeed;
    }
    else if (walkVX < -1 * maxSpeed) {
        walkVX = -1 * maxSpeed;
    }
    vX = walkVX + liftVX;

    MoveX();
    CollideX();
    std::cout << leftBlock << "," << rightBlock << std::endl;
    if (rightBlock == 2) {
        vX = -100000;
    }
    else if (leftBlock == 2) {
        vX = 100000;
    }
    

    if (walkVX >= minSpeed) {
        walkVX -= deceleration * settings::timeScale;
    }
    else if (walkVX < minSpeed && walkVX > minSpeed * -1) {
        walkVX = 0.0;
    }
    else if (walkVX <= minSpeed * -1) {
        walkVX += deceleration * settings::timeScale;
    }
    else {
        walkVX = 0.0;
    }
    aX = 0.0;


    if (y < -1000.0) {
        Die();
    }

    if (!onGround) {
        moveBody += 12 * settings::timeScale;
    }

    if (walkVX != 0.0) {
        moveBody += 12 * settings::timeScale;
    }
    else if (onGround) {
        moveBody = 0;
    }

    
}

void Player::Jump() {
    if (coyoteTime < 6 && canJump) {
        vY = 1100.0;
        canJump = false;
    }
}

void Player::CollideY() {
    headBlock = 0;
    groundBlock = 0;
    OBJRECT touchingMap;
    onGround = false;
    touchingMap = isTouchingMap(x, y, w, h);

    while (touchingMap.block && vY < 0.0) {
        touchingMap = isTouchingMap(x, y, w, h);
        onGround = true;
        vY = 0.0;
        y = touchingMap.y + 0.5 * h + levelP->GetBlockSize() * 0.5;
        groundBlock = touchingMap.block;
        //touchingMap = isTouchingMap(x, y, w, h);
    }
    while (touchingMap.block && vY > 0.0) {
        touchingMap = isTouchingMap(x, y, w, h);
        vY = 0.0;
        y = touchingMap.y - 0.5 * h - levelP->GetBlockSize() * 0.5;
        headBlock = touchingMap.block;
        //touchingMap = isTouchingMap(x, y, w, h);
    }

    if (onGround) {
        coyoteTime = 0;
        canJump = true;
    }
    else {
        coyoteTime++;
    }
}

void Player::CollideX() {
    rightBlock = 0;
    leftBlock = 0;
    OBJRECT touchingMap;
    touchingMap = isTouchingMap(x, y, w, h);
    while (touchingMap.block) {
        touchingMap = isTouchingMap(x, y, w, h);
        if (vX > 0.0) {
            vX = 0.0;
            x = touchingMap.x - 0.5 * w - levelP->GetBlockSize() * 0.5;
            rightBlock = touchingMap.block;
        }
        else if (vX < 0.0) {
            vX = 0.0;
            x = touchingMap.x + 0.5 * w + levelP->GetBlockSize() * 0.5;
            leftBlock = touchingMap.block;
        }
        else {
            break;
        }
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

void Player::Die() {
    x = 180.0;
    y = 180.0;

    Mix_Chunk* se = Mix_LoadWAV("Assets/sounds/discord.wav");
    Mix_PlayChannel(-1, se, 0);

    //Mix_Music* music = Mix_LoadMUS("Assets/audio/sanctuary.wav");
    //Mix_PlayMusic(music, -1);
}

void Player::DrawPlayer() {
    DrawPart("legL", sin(moveBody) * 16, 30, 60);
    DrawPart("legR", sin(moveBody) * -16, 34, 60);
    DrawPart("body", sin(moveBody), 0, 0);
    DrawPart("head", sin(moveBody) * 4, 80, 20);
    DrawPart("armL", sin(moveBody) * -16, 80, 50);
    DrawPart("armR", sin(moveBody) * 16, 60, 50);

    SDL_Color color = { 255,255,255,255 };
    texturesP->DrawTextA("vx:" + std::to_string(vX), color, 0, 0, 1, 1);
    texturesP->DrawTextA("vy:" + std::to_string(vY), color, 360, 0, 1, 1);
    texturesP->DrawTextA("walkVX:" + std::to_string(walkVX), color, 0, 100, 1, 1);
    texturesP->DrawTextA("liftVX:" + std::to_string(liftVX), color, 0, 200, 1, 1);
    texturesP->DrawTextA("moveBody:" + std::to_string(moveBody), color, 0, 980, 1, 1);
    texturesP->DrawTextA("onGround:" + std::to_string(onGround), color, 500, 980, 1, 1);
}

void Player::DrawPart(std::string tex, double angle, int X, int Y) {
    OBJRECT rect;
    rect.x = (int)x + 20 + flipX * -40;
    rect.y = (int)y + 5;
    rect.w = 120;
    rect.h = 120;
    OBJRECT point;
    if (flipX) {
        point.x = rect.w - X;
    }
    else {
        point.x = X;
    }
    point.y = Y;
    texturesP->DrawImageEx(tex, rect, angle, point, flipX, 0);
}