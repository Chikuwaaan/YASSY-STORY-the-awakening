#include "Player.h"
#include "namespace.h"
#include "Level.h"
#include "Camera.h"
#include "Game.h"
#include <iostream>
#include <SDL_mixer.h>
#include "Textures.h"
#include "Input.h"
#include "OverLay.h"

Level* Player::levelP = nullptr;
Camera* Player::cameraP = nullptr;
Game* Player::gameP = nullptr;
OverLay* Player::overlayP = nullptr;

Player::Player() {
    onGround = 0;
    texName = "missing";
    maxSpeed = 480.0;
    minSpeed = 16.0;
    deceleration = 2160.0;
    moveBody = 0;
    x = 200.0;
    y = 1000.0;
    w = 40.0;
    h = 70.0;
    aX = 0.0;
    aY = 0.0;
    canJump = 0;
    jumpPressed = 0;
    isJumping = 0;
    flipX = false;
    coyoteTime = 0;
    walkVX = 0.0;
    liftVX = 0.0;
    liftVY = 0.0;
    groundBlock = 0;
    headBlock = 0;
    rightBlock = 0;
    leftBlock = 0;
    isDead = 0;
    dieTime = 0;
    dieAnim = 0;
    touchingEntity = nullptr;
    stomping = 0;
}

void Player::SetAX(double acceleration) {
    aX += acceleration;
}


void Player::Update() {
    cameraP->SetTargetX(x);
    cameraP->SetTargetY(y);
    MoveCameraRoom();

    if (dieTime > 0) {
        dieTime -= settings::timeScale;
        if (dieTime < 3.0 && dieAnim) {
            dieAnim = 0;
            overlayP->PinHole(2000, 1000, 1.0, { 0,0,0,255 });
        }
        return;
    }
    if (isDead) {
        isDead = 0;
        Spawn();
    }

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

    liftVX = 0.0;

    



    //Y
    if (vY > 1200) {
        vY = 1200;
    }
    else if (vY < -1200) {
        vY = -1200;
    }

    vY += platformer::gravity * settings::timeScale;

    MoveY();
    CollideY();

    //ギミック
    if (groundBlock == 3) {
        Die();
    }
    else if (headBlock == 3) {
        Die();
    }

    if (touchingEntity != nullptr) {
        EntityType type = touchingEntity->GetType();
        if (type == EntityType::Zako) {
            if (stomping) {
                touchingEntity->Damage();
                vY = 300;
                onGround = 1;
            }
            else {
                Die();
            }
        }
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

    //ギミック
    if (rightBlock == 3) {
        Die();
    }
    else if (leftBlock == 3) {
        Die();
    }


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
        vY = 800.0;
        canJump = false;
        onGround = false;
        isJumping = 1;
    }

    if (0 < isJumping && isJumping < 30) {
        vY = 600 + isJumping * 10.0;
        if (vY > 840) {
            vY = 840;
        }

        isJumping++;
    }

    if (!jumpPressed && isJumping) {
        isJumping = 0;
    }
}

void Player::CollideY() {
    if (onGround) {
        coyoteTime = 0;
        canJump = true;
        isJumping = 0;
    }
    else {
        coyoteTime++;
    }

    touchingEntity = nullptr;
    stomping = 0;
    onGround = false;
    OBJRECT pRect = { x,y,w,h };

    //block
    headBlock = 0;
    groundBlock = 0;

    OBJRECT bRect = levelP->IsTouching2(pRect, 0);
    if (bRect.block && vY < 0.0) {
        onGround = true;
        vY = 0.0;
        y = bRect.y + bRect.h / 2 + h / 2;
        groundBlock = bRect.block;
    }
    if (bRect.block && vY > 0.0) {
        vY = 0.0;
        isJumping = 0;
        y = bRect.y - bRect.h / 2 - h / 2;
        headBlock = bRect.block;
    }

    //entity
    for (auto& p : gameP->objects) {
        OBJRECT eRect = p->GetRect();
        bool collision = p->GetCollosion();

        if (collision && utilities::HitDetection(pRect, eRect)) {
            
            double v = p->GetVX();
            if (v > 0) {
                x += (v + 0.01) * settings::timeScale;
            }
            else if (v < 0) {
                x += (v - 0.01) * settings::timeScale;
            }
            pRect = { x,y,w,h };
            
        }

        if (utilities::HitDetection(pRect, eRect)) {
            touchingEntity = p.get();
            collision = p->GetCollosion();
            if ((pRect.y - pRect.h / 2) > eRect.y) {
                if (collision) {
                    onGround = true;
                    y = eRect.y + eRect.h / 2 + h / 2 + 0.01;
                    double v = p->GetVY();
                    if (v < 0) {
                        vY = v;
                    }
                    else if (v > 0) {
                        vY = v * -1;
                    }
                }
                else {
                    if (vY < 0) {
                        stomping = 1;
                    }
                }
            }

            else if (collision && pRect.y < eRect.y) {
                double v = p->GetVY();
                if (v < 0.0) {
                    vY = p->GetVY();
                }
                else {
                    vY = 0.0;
                }

                if (groundBlock) {
                    Die();
                }

                isJumping = 0;
                y = eRect.y - eRect.h / 2 - h / 2;
            }
        }
    }
}

void Player::CollideX() {
    SDL_Color color = { 255,255,255,255 };
    rightBlock = 0;
    leftBlock = 0;
    OBJRECT pRect = { x,y,w,h };
    OBJRECT bRect = levelP->IsTouching2(pRect, 1);

    if (bRect.block) {
        bRect = levelP->IsTouching2(pRect, 1);
        if (vX > 0.0) {
            if (!liftVX) {
                walkVX = 0.0;
            }
            vX = 0.0;
            x = bRect.x - 0.5 * w - bRect.w * 0.5;
            rightBlock = bRect.block;
        }
        else if (vX < 0.0) {
            if (!liftVX) {
                walkVX = 0.0;
            }
            vX = 0.0;
            x = bRect.x + 0.5 * w + bRect.w * 0.5;
            leftBlock = bRect.block;
        }
    }

    
    for (auto& p : gameP->objects) {
        OBJRECT eRect = p->GetRect();
        bool collision = p->GetCollosion();

        if (utilities::HitDetection(pRect, eRect)) {
            touchingEntity = p.get();
            if (collision && pRect.x > eRect.x) {
                if (!liftVX) {
                    walkVX = 0.0;
                }
                vX = 0.0;
                x = eRect.x + 0.5 * w + eRect.w * 0.5;
            }
            
            else if (collision && pRect.x < eRect.x) {
                if (!liftVX) {
                    walkVX = 0.0;
                }
                vX = 0.0;
                x = eRect.x - 0.5 * w - eRect.w * 0.5;
            }
            
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
    isDead = 1;
    dieTime = 3.0;
    dieAnim = 1;

    Mix_Chunk* se = Mix_LoadWAV("Assets/sounds/die.wav");
    Mix_PlayChannel(-1, se, 0);
    //Mix_Music* music = Mix_LoadMUS("Assets/audio/sanctuary.wav");
    //Mix_PlayMusic(music, -1);
}

void Player::Spawn() {
    x = 45.0;
    y = 300.0;
    vX = 0.0;
    vY = 0.0;
    aX = 0.0;
    aY = 0.0;
    walkVX = 0.0;
    liftVX = 0.0;

    overlayP->FadeOut(1, {0,0,0,255});
    CAMERA cam = cameraP->GetCam();
    cam.x = x;
    cam.y = y;
    cameraP->SetCam(cam);

    gameP->SetupEntities();
}

void Player::DrawPlayer() {
    DrawPart("legL", sin(moveBody) * 16, 30, 50);
    DrawPart("legR", sin(moveBody) * -16, 20, 50);
    DrawPart("body", 0, 0, 0);
    DrawPart("head", sin(moveBody) * 4, 60, 30);
    DrawPart("armL", sin(moveBody) * -16, 70, 50);
    DrawPart("armR", sin(moveBody) * 16, 55, 50);

    SDL_Color color = { 255,255,255,255 };
}


void Player::DrawPart(std::string tex, double angle, double X,double Y) {
    OBJRECT rect;
    rect.x = (int)x + 20 + flipX * -40;
    rect.y = (int)y + 5;
    rect.w = 110;
    rect.h = 110;
    OBJRECT point;
    if (flipX) {
        point.x = rect.w - X;
    }
    else {
        point.x = X;
    }
    point.y = Y;
    texturesP->DrawImage(tex, rect, 1, {1, angle, point.x, point.y, flipX});
}