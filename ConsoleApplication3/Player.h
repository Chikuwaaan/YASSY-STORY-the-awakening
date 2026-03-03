#pragma once
#include <string>
#include "structs.h"
#include "GameObject.h"

class Level;
class Camera;
class Game;
class OverLay;

class Player :
    public GameObject
{
private:
    bool onGround;
    double maxSpeed;
    double minSpeed;
    double deceleration;
    double moveBody;
    double walkVX;
    double liftVX, liftVY;
    double aX, aY;
    bool canJump;
    bool jumpPressed;
    bool isJumping;
    double jumpingTime;
    double coyoteTime;
    double gravity;
    int groundBlock, headBlock, rightBlock, leftBlock;

    bool isDead;
    double dieTime;
    bool dieAnim;
    GameObject* touchingEntity;
    bool stomping;

    
    double spawnX, spawnY;

    void CollideY();
    void CollideX();
public:
    int currentCP;
    static Level* levelP;
    static Camera* cameraP;
    static OverLay* overlayP;
    Player();
    void SetAX(double acceleration);
    void Update() override;
    void Jump();
    void Stomp();
    
    void MoveCameraRoom();
    void Die();
    void Spawn();
    void SetSpawnPoint(double x, double y);

    void Draw() override;
    void DrawPart(std::string tex, double angle, double x, double y);
};

