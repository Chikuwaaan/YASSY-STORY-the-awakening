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
    onGround = 0;
    texName = "missing";
    maxSpeed = 480.0;
    minSpeed = 16.0;
    deceleration = 2160.0;
    moveBody = 0;
    x = 0.0;
    y = 1000.0;
    w = 60.0;
    h = 80.0;
    aX = 0.0;
    aY = 0.0;
    canJump = 0;
    isJumping = 0;
    flipX = false;
    coyoteTime = 0;
    walkVX = 0.0;
    liftVX = 0.0;
    groundBlock = 0;
    headBlock = 0;
    rightBlock = 0;
    leftBlock = 0;
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
        jumpPressed = 1;
    }
    else {
        jumpPressed = 0;
    }
    Jump();

    if (keystate[SDL_SCANCODE_A]) {
        SetAX(-2160.0);
        FlipX(true);
    }
    if (keystate[SDL_SCANCODE_D]) {
        SetAX(2160.0);
        FlipX(false);
    }
    if (keystate[SDL_SCANCODE_M]) {
        h++;
    }
    

    //Y
    vY += platformer::gravity * settings::timeScale;
    MoveY();
    CollideY();
    //std::cout << groundBlock;

 
    liftVX = 0;

    if (groundBlock == 2) {
        vY = 1300.0;
    }
    else if (headBlock == 2) {
        vY = -1000.0;
    }
    else if (headBlock == 3) {
        Die();
    }
    else if (groundBlock == 3) {
        Die();
    }
    else if (groundBlock == 4) {
        liftVX = -360;
    }


    //X
    if (onGround) {
        if (aX) {
            walkVX += aX * settings::timeScale;
        }
        else {
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
        }
    }
    else {
        if (aX) {
            walkVX += aX * settings::timeScale * 0.5;
        }
        else {
            if (walkVX >= minSpeed) {
                walkVX -= deceleration * settings::timeScale * 0.5;
            }
            else if (walkVX < minSpeed && walkVX > minSpeed * -1) {
                walkVX = 0.0;
            }
            else if (walkVX <= minSpeed * -1) {
                walkVX += deceleration * settings::timeScale * 0.5;
            }
            else {
                walkVX = 0.0;
            }
        }
    }
    

    if (walkVX > maxSpeed) {
        walkVX = maxSpeed;
    }
    else if (walkVX < -1 * maxSpeed) {
        walkVX = -1 * maxSpeed;
    }
    if (onGround) {
        vX = walkVX + liftVX;
    }
    else {
        vX = walkVX + liftVX * 0.5;
    }
    

    MoveX();
    CollideX();
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
    if (jumpPressed && coyoteTime < 6 && canJump) {
        vY = 600.0;
        canJump = false;
        isJumping = 1;
    }

    if (0 < isJumping && isJumping < 30) {
        vY = 500.0 + isJumping * 14.0;
        if (vY > 800.0) vY = 800.0;
        isJumping++;
    }

    if (!jumpPressed && isJumping) {
        std::cout << isJumping << std::endl;
        isJumping = 0;
    }
}

void Player::CollideY() {
    SDL_Color color = { 255,255,255,255 };
    headBlock = 0;
    groundBlock = 0;
    onGround = false;
    OBJRECT pRect = { x,y,w,h };
    OBJRECT bRect = levelP->IsTouching2(pRect, 0);
    texturesP->DrawTextA(std::to_string(bRect.block), color, 1340, 0, 1, 1);

    if (bRect.block && vY < 0.0) {
        bRect = levelP->IsTouching2(pRect, 0);
        onGround = true;
        vY = 0.0;
        y = bRect.y + bRect.h / 2 + h / 2;
        groundBlock = bRect.block;
    }
    if (bRect.block && vY > 0.0) {
        bRect = levelP->IsTouching2(pRect, 0);
        vY = 0.0;
        isJumping = 0;
        y = bRect.y - bRect.h / 2 - h / 2;
        headBlock = bRect.block;
    }


    if (onGround) {
        coyoteTime = 0;
        canJump = true;
        isJumping = 0;
    }
    else {
        coyoteTime++;
    }

}

void Player::CollideX() {
    SDL_Color color = { 255,255,255,255 };
    rightBlock = 0;
    leftBlock = 0;
    OBJRECT pRect = { x,y,w,h };
    OBJRECT bRect = levelP->IsTouching2(pRect, 1);
    texturesP->DrawTextA(std::to_string(bRect.block), color, 1340, 50, 1, 1);

    if (bRect.block) {
        bRect = isTouchingMap(x, y, w, h);
        if (vX > 0.0) {
            if (!liftVX){
                walkVX = 0.0;
            }
            vX = 0.0;
            x = bRect.x - 0.5 * w - bRect.w * 0.5;
            rightBlock = bRect.block;
        }
        else if (vX < 0.0) {
            if (!liftVX){
                walkVX = 0.0;
            }
            vX = 0.0;
            x = bRect.x + 0.5 * w + bRect.w * 0.5;
            leftBlock = bRect.block;
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
    x = 45.0;
    y = 300.0;
    vX = 0.0;
    vY = 0.0;
    aX = 0.0;
    aY = 0.0;
    walkVX = 0.0;
    liftVX = 0.0;

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
    texturesP->DrawTextA("x:" + std::to_string(x), color, 0, 0, 1, 1);
    texturesP->DrawTextA("y:" + std::to_string(y), color, 500, 0, 1, 1);
    texturesP->DrawTextA("vx:" + std::to_string(vX), color, 0, 50, 1, 1);
    texturesP->DrawTextA("vy:" + std::to_string(vY), color, 500, 50, 1, 1);
    texturesP->DrawTextA("walkVX:" + std::to_string(walkVX), color, 0, 100, 1, 1);
    texturesP->DrawTextA("liftVX:" + std::to_string(liftVX), color, 500, 100, 1, 1);
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