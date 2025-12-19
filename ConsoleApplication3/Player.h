#pragma once
#include <string>
#include "structs.h"
#include "GameObject.h"

class Level;
class Camera;

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
    double liftVX;
    double aX, aY;
    int coyoteTime;
    int groundBlock, headBlock, rightBlock, leftBlock;
public:
    bool canJump;
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

