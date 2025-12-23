#pragma once

#include <string>
#include <vector>
#include "structs.h"

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
public:
    

    static Textures* texturesP;
    static Camera* cameraP;
    static Input* inputP;

    virtual void Update() = 0;
    GameObject();
    void MoveX();
    void MoveY();
    OBJRECT GetRect();
    double GetVX();
    COLLISION GetCollosion();
    void Draw();
    void FlipX(bool flip);
};

