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
#include <windows.h>

Level* Player::levelP = nullptr;
Camera* Player::cameraP = nullptr;
OverLay* Player::overlayP = nullptr;

Player::Player() : 
    eye1(10),
    eye2(10)
{
    vYreserve = 0;
    onGround = 0;
    texName = "head";
    maxSpeed = 480.0;
    minSpeed = 16.0;
    deceleration = 2160.0;
    moveBody = 0;
    x = 200.0;
    y = 1000.0;
    w = 32.0;
    h = 64.0;
    aX = 0.0;
    aY = 0.0;
    canJump = 0;
    jumpPressed = 0;
    isJumping = 0;
    jumpingTime = 0.0;
    flipX = false;
    coyoteTime = 0;
    gravity = platformer::gravity;
    walkVX = 0.0;
    liftVX = 0.0;
    liftVY = 0.0;
    groundBlock = 0;
    headBlock = 0;
    rightBlock = 0;
    leftBlock = 0;
    initCam = true;

    stop = 0;
    isDead = 0;
    dieTime = 0;
    dieAnim = 0;
    touchingEntity = nullptr;
    stomping = 0;

    stucking = 0;
    watering = 0;

    spawnX = 0;
    spawnY = 0;

    completing = 0;
}

void Player::SetAX(double acceleration) {
    aX += acceleration;
}

void Player::AddVY(double amount) {
    vY += amount;
    if (amount >= 0) {
        jumpingTime = 1;
    }
}

void Player::Update() {
    MoveCameraRoom();

    if (dieTime > 0) {
        dieTime -= settings::timeScale;
        if (dieTime < 3.0 && dieAnim) {
            dieAnim = 0;
            //overlayP->PinHole(2000, 1000, 1.1, { 0,0,0,255 });
        }
        stop = 1;
    }
    else {
        stop = 0;
    }

    /*
    if (completing) {
        stop = 1;
        timerComplete.Update();
        if (timerComplete.GetTime() > 1) {
            timerComplete.Reset();
            Complete();
        }
    }
    */

    if (stop) return;

    if (isDead) {
        isDead = 0;
        Spawn();
    }
    
    
    EVENT event = inputP->event;
    const Uint8* keystate = inputP->keystate;
    
    if (inputP->config[Action::HoldJump].on) {
        jumpPressed = 1;
    }
    else {
        jumpPressed = 0;
    }
    Jump();

    if (inputP->config[Action::HoldLeft].on) {
        if (stucking) {
            if (onGround) {
                SetAX(-540.0);
            }
            else {
                SetAX(-1080.0);
            }
        }
        else {
            SetAX(-2160.0);
        }

        FlipX(true);
    }

    if (inputP->config[Action::HoldRight].on) {
        if (stucking) {
            if (onGround) {
                SetAX(540.0);
            }
            else {
                SetAX(1080.0);
            }
        }
        else {
            SetAX(2160.0);
        }

        FlipX(false);
    }

    if (inputP->config[Action::HoldRun].on != savedata::InvertDash) {
        if (stucking) {
            maxSpeed = 320.0;
            moveBody += 48 * settings::timeScale;
        }
        else {
            maxSpeed = 640.0;
            moveBody += 12 * settings::timeScale;
        }
    }
    else {
        if (stucking) {
            maxSpeed = 240.0;
        }
        else {
            maxSpeed = 480.0;
        }
    }
    

    liftVX = 0.0;
    if (watering && (vX || vY)) {
        platformerP->AddObject("Particle", {x, y, "splash"});
    }
    if (stucking && onGround && vX) {
        platformerP->AddObject("Particle", { x, y-32, "mud" });
    }
    watering = 0;



    //Y
    if (vY < -1200) {
        vY = -1200;
    }

    vY +=gravity * settings::timeScale;

    MoveY();
    CollideY();
    if (vYreserve) {
        vY = vYreserve;
    }
    vYreserve = 0;
    
    if (isDead) {
        return;
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
    /*
    if (touchingEntity != nullptr) {
        EntityType type = touchingEntity->GetType();
        if (stomping) {
            touchingEntity->Stomped();
        }
        else {
            touchingEntity->Touched();
        }
    }
    */

    

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
    if (jumpPressed && coyoteTime < 0.05 && canJump) {
        if (stucking) {
            vY = 500.0;
        }
        else {
            vY = 660.0;
        }
        canJump = false;
        onGround = false;
        isJumping = true;
        jumpingTime = 0.0;
        //Mix_Chunk* se = Mix_LoadWAV("Assets/sounds/player_jump.mp3");
        //Mix_PlayChannel(-1, se, 0);
        soundsP->PlaySE("player_jump");
    }

    if (isJumping) {
        jumpingTime += settings::timeScale;
    }
    else {
        jumpingTime = 0.0;
    }

    if (!watering) {
        if (!stucking && isJumping && vY > 0 && jumpingTime < 0.5) {
            gravity = platformer::gravity * 0.2;
        }
        else if (stucking && isJumping && vY > 0 && jumpingTime < 0.3) {
            gravity = platformer::gravity * 0.4;
        }
        else {
            gravity = platformer::gravity;
        }
    }
    else {
        if (!stucking && isJumping && vY > 0 && jumpingTime < 0.5) {
            gravity = platformer::gravity * 0.1;
        }
        else if (stucking && isJumping && vY > 0 && jumpingTime < 0.3) {
            gravity = platformer::gravity * 0.2;
        }
        else {
            gravity = platformer::gravity * 0.5;
        }
    }
    

    if (!jumpPressed && isJumping) {
            isJumping = false;
    }
    /*
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
    */
}

void Player::Stomp() {
    vYreserve = 600;
    onGround = 1;
}

void Player::JumpPadded(double amount) {
    vYreserve = amount;
    stucking = false;
    isJumping = false;
    coyoteTime = 1008;
}

void Player::Land() {

}

bool Player::IsDead() {
    return isDead;
}

void Player::CollideY() {
    if (onGround) {
        coyoteTime = 0;
        canJump = true;
        isJumping = 0;
    }
    else {
        coyoteTime += settings::timeScale;
    }

    touchingEntity = nullptr;
    stomping = 0;
    onGround = false;
    OBJRECT pRect = { x,y,w,h };

    //block
    headBlock = 0;
    groundBlock = 0;

    OBJRECT bRect = levelP->IsTouching2(pRect, 0);
    if (bRect.block) {
        if (bRect.block && vY < 0.0) {
            onGround = true;
            vY = 0.0;
            y = bRect.y + bRect.h / 2 + h / 2;
            groundBlock = bRect.block;

            if (levelP->blockProperty[bRect.block].stuck) {
                stucking = 1;
            }
            else {
                stucking = 0;
            }
            if (levelP->blockProperty[bRect.block].conveyor) {
                liftVX = levelP->blockProperty[bRect.block].conveyor;
            }
            else {
                liftVX = 0;
            }
        }
        if (bRect.block && vY > 0.0) {
            vY = 0.0;
            isJumping = 0;
            y = bRect.y - bRect.h / 2 - h / 2;
            headBlock = bRect.block;
        }

        if (levelP->blockProperty[bRect.block].damage) {
            Die();
        }
    }

    //entity
    for (auto& p : platformerP->objects) {
        OBJRECT eRect = p->GetRect();
        bool collision = p->GetCollosion();

        //collisionあるときのリフト
        if (utilities::HitDetection(pRect, eRect)) {
            if (collision) {
                double v = p->GetVX();
                if (v > 0) {
                    x += (v + 0.01) * settings::timeScale;
                }
                else if (v < 0) {
                    x += (v - 0.01) * settings::timeScale;
                }
                pRect = { x,y,w,h };

                OBJRECT bRect = levelP->IsTouching2(pRect, 1);
                if (bRect.block) Die();
                }

            //秘儀・めり込みもどし
            if (utilities::HitDetection(pRect, eRect)) {
                if (pRect.y > eRect.y) {
                    if (collision) {
                        onGround = true;
                        stucking = 0;
                        y = eRect.y + eRect.h / 2 + h / 2 + 0.01;
                        double v = p->GetVY();
                        if (v < 0) {
                            vY = v;
                        }
                        else if (v > 0) {
                            vY = v * -1;
                        }
                        else if (v == 0) {
                            vY = v;
                        }
                    }
                    if (vY - p->GetVY() <= 0) {
                        p->Stomped();
                        p->onStomp = 1;
                    }
                } 
                else if (pRect.y < eRect.y) {
                    if (collision) {
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
    }
}

void Player::CollideX() {
    rightBlock = 0;
    leftBlock = 0;
    OBJRECT pRect = { x,y,w,h };
    OBJRECT bRect = levelP->IsTouching2(pRect, 1);


    if (bRect.block) {
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

        if (levelP->blockProperty[bRect.block].damage) {
            Die();
        }
    }

    for (auto& p : platformerP->objects) {
        OBJRECT eRect = p->GetRect();
        bool collision = p->GetCollosion();

        if (utilities::HitDetection(pRect, eRect)) {
            if (!(p->onStomp)) p->Touched();
            p->onStomp = 0;
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
    if (platformerP->autoScroll != 0.0) {
        cameraP->SetTargetX(platformerP->scrollPos);
        CAMERA cam = cameraP->GetCam();
        cam.x = platformerP->scrollPos;
        cameraP->SetCam(cam);

        if (cam.x >= 54048) platformerP->autoScroll = 0.0;
    }
    else {
        cameraP->SetTargetX(x);
    }
    cameraP->SetTargetY(y);

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

            if ((*room)[i].force || initCam) {
                if (camera.x < (*room)[i].x3) camera.x = (*room)[i].x3;
                if (camera.x > (*room)[i].x4) camera.x = (*room)[i].x4;
                if (camera.y < (*room)[i].y3) camera.y = (*room)[i].y3;
                if (camera.y > (*room)[i].y4) camera.y = (*room)[i].y4;
                if (initCam) initCam = false;
            }
        }
    }
    cameraP->SetCam(camera);
}

void Player::Die() {
    texName = "head_miss";
    soundsP->PlaySE("die");
    platformer::death++;
    isDead = 1;
    dieTime = 3.0;
    dieAnim = 1;
    overlayP->PinHole(settings::baseW/2, settings::baseH/2, 2000, 1000, 1.1, {0,0,0,255});
}

void Player::Spawn() {
    texName = "head";
    
    vX = 0.0;
    vY = 0.0;
    aX = 0.0;
    aY = 0.0;
    walkVX = 0.0;
    liftVX = 0.0;
    flipX = 0;

    initCam = 1;
    stop = 0;
    overlayP->FadeIn(1, {0,0,0,255});
    
    platformerP->Spawn();
    x = spawnX;
    y = spawnY;

    cameraP->LoadCameraRoom(platformer::level);
    CAMERA cam = cameraP->GetCam();
    cam.x = cam.targetX;
    cam.y = cam.targetY;
    cameraP->SetCam(cam);
}

void Player::SetSpawnPoint(double x, double y) {
    spawnX = x;
    spawnY = y;
}

double Player::GetSpawnX() {
    return spawnX;
}

double Player::GetSpawnY() {
    return spawnY;
}

void Player::Goal() {
    if (completing) return;
    stop = 0;

    platformerP->Complete();
    platformerP->Save();
    completing = 1;
    std::cout << "GOAL";
}

void Player::Draw() {
    DrawPart("legL", sin(moveBody) * 16, 30, 50);
    DrawPart("legR", sin(moveBody) * -16, 20, 50);
    DrawPart("body", 0, 0, 0);
    DrawPart(texName, sin(moveBody) * 4, 60, 30);
    DrawPart("armL", sin(moveBody) * -16, 70, 50);
    DrawPart("armR", sin(moveBody) * 16, 55, 50);

    if (!savedata::Eye) return;
    double vx, vy;
    if (isDead) {
        vx = 0;
        vy = 0;
    }
    else {
        vx = vX;
        vy = vY;
    }

    eye1.SetX(x + 25 - flipX * 50);
    eye1.SetY(y + 45);
    eye1.Update(vx, vy);
    eye1.Draw();
    eye2.SetX(x + 45 - flipX * 90);
    eye2.SetY(y + 42);
    eye2.Update(vx, vy);
    eye2.Draw();
    //eye2.Update();
    //eye2.Draw();
}

void Player::DrawPart(std::string tex, double angle, double X,double Y) {
    OBJRECT rect;
    rect.x = (int)x + 20 + flipX * -40;
    rect.y = (int)y + 10;
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

void Player::DrawA() {
    DrawPartA("legL", sin(moveBody) * 16, 30, 50);
    DrawPartA("legR", sin(moveBody) * -16, 20, 50);
    DrawPartA("body", 0, 0, 0);
    DrawPartA("head", sin(moveBody) * 4, 60, 30);
    DrawPartA("armL", sin(moveBody) * -16, 70, 50);
    DrawPartA("armR", sin(moveBody) * 16, 55, 50);
}

void Player::DrawPartA(std::string tex, double angle, double X, double Y) {
    OBJRECT rect;
    rect.x = (int)x + 20 + flipX * -40;
    rect.y = (int)y + 10;
    rect.w = 110;
    rect.h = 110;
    OBJRECT point;
    point.x = rect.w - X;
    point.y = Y;
    texturesP->DrawImage(tex, rect, 0, { 1, angle, point.x, point.y, flipX });
}