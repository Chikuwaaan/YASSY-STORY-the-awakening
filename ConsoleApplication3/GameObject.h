#pragma once

#include <string>
#include <vector>
#include "structs.h"
#include "namespace.h"

class Level;
class Textures;
class Sounds;
class Camera;
class Input;
class Platformer;
class Player;


enum class EntityType {
    Null,
    Lift,
    Zako,
    CheckPoint,
    BackGround
};

class GameObject
{
protected:
    std::string texName;
    double x, y, w, h;
    double vX, vY;
    bool flipX;
    EntityType type;
    bool collision;
    bool rigid;
    

    int groundBlock, headBlock, rightBlock, leftBlock;
    GameObject* touchingEntity;

    void CollideY();
    void CollideX();
public:
    bool dead;
    bool onStomp;
    bool alwaysLoad;

    static Level* levelP;
    static Textures* texturesP;
    static Sounds* soundsP;
    static Camera* cameraP;
    static Input* inputP;
    static Platformer* platformerP;
    static Player* playerP;

    virtual void Update() {};
    virtual void Touched() {};
    virtual void Stomped() {};
    virtual ~GameObject() = default;
    GameObject();
    EntityType GetType();
    bool IsDead();
    void MoveX();
    void MoveY();
    void SetX(double pos);
    void SetY(double pos);
    OBJRECT GetRect();
    double GetVX();
    double GetVY();
    bool GetCollosion();
    virtual void Draw();
    void DrawHitbox();
    void FlipX(bool flip);
};

