#pragma once

#include <string>
#include <vector>
#include "structs.h"
#include "namespace.h"

class Textures;
class Camera;
class Input;

class GameObject
{
protected:
    std::string texName;
    double x, y, w, h;
    double vX, vY;
    bool flipX;
    COLLISION collision;
    entityType type;
    
public:
    bool dead;

    static Textures* texturesP;
    static Camera* cameraP;
    static Input* inputP;

    virtual void Update() {};
    virtual void Damage() {};
    GameObject();
    entityType GetType();
    bool IsDead();
    void MoveX();
    void MoveY();
    OBJRECT GetRect();
    double GetVX();
    COLLISION GetCollosion();
    void Draw();
    void FlipX(bool flip);
};

