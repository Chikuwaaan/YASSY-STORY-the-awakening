#pragma once
#include <string>
#include "structs.h"
#include "GameObject.h"

class Level;
class Camera;
class Game;

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
    int isJumping;
    int coyoteTime;
    int groundBlock, headBlock, rightBlock, leftBlock;
    GameObject* touchingEntity;
public:
    static Game* gameP;
    static Level* levelP;
    static Camera* cameraP;
    Player();
    void SetAX(double acceleration);
    OBJRECT isTouchingMap(double x, double y, double w, double h);
    void Update() override;
    void Jump();
    void CollideY();
    void CollideX();
    void MoveCameraRoom();
    void Die();
    
    void DrawPlayer();
    void DrawPart(std::string tex, double angle, int x, int y);
};

