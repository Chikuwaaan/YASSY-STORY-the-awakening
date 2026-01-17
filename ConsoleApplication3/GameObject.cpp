#include <iostream>
#include "GameObject.h"
#include "namespace.h"
#include "structs.h"
#include "Textures.h"
#include "Input.h"
#include "Level.h"
#include "Player.h"

Textures* GameObject::texturesP = nullptr;
Sounds* GameObject::soundsP = nullptr;
Camera* GameObject::cameraP = nullptr;
Input* GameObject::inputP = nullptr;
Level* GameObject::levelP = nullptr;
Player* GameObject::playerP = nullptr;

GameObject::GameObject() {
    type = EntityType::Null;
    x = 0.0;
    y = 0.0;
    w = 180.0;
    h = 180.0;
    vX = 0.0;
    vY = 0.0;
    collision = 0;
    dead = 0;
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

void GameObject::Draw() {
    OBJRECT rect = { x,y,w,h };
    texturesP->DrawImage(texName, rect, 1, {});

}

void GameObject::FlipX(bool flip) {
    flipX = flip;
}