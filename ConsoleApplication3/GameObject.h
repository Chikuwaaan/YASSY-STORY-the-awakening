#pragma once

#include <string>
#include <vector>
#include "structs.h"
#include "namespace.h"

class Textures;
class Sounds;
class Camera;
class Input;


class GameObject
{
protected:
    std::string texName;
    double x, y, w, h;
    double vX, vY;
    bool flipX;
    EntityType type;
    bool collision;
public:
    bool dead;

    static Textures* texturesP;
    static Sounds* soundsP;
    static Camera* cameraP;
    static Input* inputP;

    virtual void Update() {};
    virtual void Touched() {};
    virtual void Stomped() {};
    virtual ~GameObject() = default;
    GameObject();
    EntityType GetType();
    bool IsDead();
    void MoveX();
    void MoveY();
    OBJRECT GetRect();
    double GetVX();
    double GetVY();
    bool GetCollosion();
    void Draw();
    void FlipX(bool flip);
};

