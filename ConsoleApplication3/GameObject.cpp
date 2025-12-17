#include "GameObject.h"
#include "namespace.h"
#include "structs.h"
#include "Textures.h"
#include "Input.h"

Textures* GameObject::texturesP = nullptr;
Camera* GameObject::cameraP = nullptr;
Input* GameObject::inputP = nullptr;

GameObject::GameObject() {
    x = 0.0;
    y = 0.0;
    w = 200.0;
    h = 200.0;
    vX = 0.0;
    vY = 0.0;
}

void GameObject::MoveX() {
    x += vX * settings::timeScale;
}

void GameObject::MoveY() {
    y += vY * settings::timeScale;
}

void GameObject::Draw() {
    OBJRECT rect = { x,y,w,h };
    texturesP->DrawImage(texName, rect);

}

void GameObject::FlipX(bool flip) {
    flipX = flip;
}