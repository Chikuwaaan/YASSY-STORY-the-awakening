#include <iostream>
#include "GameObject.h"
#include "namespace.h"
#include "Level.h"
#include "Textures.h"
#include "Input.h"
#include "Platformer.h"
#include "Player.h"

Level* GameObject::levelP = nullptr;
Textures* GameObject::texturesP = nullptr;
Sounds* GameObject::soundsP = nullptr;
Camera* GameObject::cameraP = nullptr;
Input* GameObject::inputP = nullptr;
Platformer* GameObject::platformerP = nullptr;
Player* GameObject::playerP = nullptr;

GameObject::GameObject() {
    type = EntityType::Null;
    x = 0.0;
    y = 0.0;
    w = 180.0;
    h = 180.0;
    vX = 0.0;
    vY = 0.0;
    liftVX = 0.0;

    flipX = 0;
    collision = 0;
    rigid = 0;
    layer = -1;

    visible = 1;
    dead = 0;
    onStomp = 0;
    alwaysLoad = 0;
}

void GameObject::CollideY() {
    /*
    if (onGround) {
        coyoteTime = 0;
        canJump = true;
        isJumping = 0;
    }
    else {
        coyoteTime++;
    }
    */

    touchingEntity = nullptr;
    OBJRECT pRect = { x,y,w,h };
    onGround = false;

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

            if (levelP->blockProperty[bRect.block].conveyor) {
                liftVX = levelP->blockProperty[bRect.block].conveyor;
            }
            else {
                liftVX = 0;
            }
        }
        if (bRect.block && vY > 0.0) {
            vY = 0.0;
            y = bRect.y - bRect.h / 2 - h / 2;
            headBlock = bRect.block;
        }

        if (levelP->blockProperty[bRect.block].damage == 2) {
            dead = 1;
        }
    }

    //entity
    for (auto& p : platformerP->objects) {
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
            }

            else if (collision && pRect.y < eRect.y) {
                double v = p->GetVY();
                if (v < 0.0) {
                    vY = p->GetVY();
                }
                else {
                    vY = 0.0;
                }
                y = eRect.y - eRect.h / 2 - h / 2;
            }
        }
    }
}

void GameObject::CollideX() {
    SDL_Color color = { 255,255,255,255 };
    rightBlock = 0;
    leftBlock = 0;
    OBJRECT pRect = { x,y,w,h };
    OBJRECT bRect = levelP->IsTouching2(pRect, 1);

    if (bRect.block) {
        if (vX > 0.0) {
            vX = 0.0;
            x = bRect.x - 0.5 * w - bRect.w * 0.5;
            rightBlock = bRect.block;
        }
        else if (vX < 0.0) {
            vX = 0.0;
            x = bRect.x + 0.5 * w + bRect.w * 0.5;
            leftBlock = bRect.block;
        }

        if (levelP->blockProperty[bRect.block].damage == 2) {
            dead = 1;
        }
    }

    for (auto& p : platformerP->objects) {
        OBJRECT eRect = p->GetRect();
        bool collision = p->GetCollosion();

        if (utilities::HitDetection(pRect, eRect)) {
            touchingEntity = p.get();
            if (collision && pRect.x > eRect.x) {
                vX = 0.0;
                x = eRect.x + 0.5 * w + eRect.w * 0.5;
            }

            else if (collision && pRect.x < eRect.x) {
                vX = 0.0;
                x = eRect.x - 0.5 * w - eRect.w * 0.5;
            }

        }
    }
}

EntityType GameObject::GetType() {
    return type;
}

bool GameObject::IsDead() {
    return dead;
}

void GameObject::MoveX() {
    x += vX * settings::timeScale;
}

void GameObject::MoveY() {
    y += vY * settings::timeScale;
}

void GameObject::SetX(double pos) {
    x = pos;
}

void GameObject::SetY(double pos) {
    y = pos;
}

OBJRECT GameObject::GetRect() {
    OBJRECT Rect;
    Rect.x = x;
    Rect.y = y;
    Rect.w = w;
    Rect.h = h;
    return Rect;
}

double GameObject::GetVX() {
    return vX;
}

double GameObject::GetVY() {
    return vY;
}

bool GameObject::GetCollosion() {
    return collision;
}

int GameObject::GetLayer() {
    return layer;
}

void GameObject::Draw() {
    OBJRECT rect = { x,y,w,h };
    texturesP->DrawImage(texName, rect, 1, {});

}

void GameObject::DrawHitbox() {
    OBJRECT rect = { x,y,w,h };
    texturesP->DrawRect({255,0,0,255}, rect, 1);
}

void GameObject::FlipX(bool flip) {
    flipX = flip;
}