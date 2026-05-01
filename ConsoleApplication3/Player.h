#pragma once
#include <string>
#include "structs.h"
#include "GameObject.h"
#include "GameTimer.h"

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
    bool initCam;

    bool stop;
    bool isDead;
    double dieTime;
    bool dieAnim;
    GameObject* touchingEntity;
    bool stomping;

    bool stucking;
    
    
    double spawnX, spawnY;

    GameTimer timerComplete;
    bool completing;

    void CollideY();
    void CollideX();
public:
    double vYreserve;
    bool watering;

    static Level* levelP;
    static Camera* cameraP;
    static OverLay* overlayP;
    Player();
    void SetAX(double acceleration);
    void Update() override;
    void Jump();
    void Stomp();
    void JumpPadded(double amount);
    void Land();
    
    void MoveCameraRoom();
    void Die();
    void Spawn();
    void SetSpawnPoint(double x, double y);
    void Goal();
    void Complete();

    void Draw() override;
    void DrawPart(std::string tex, double angle, double x, double y);
};

