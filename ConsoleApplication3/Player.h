#pragma once
#include "GameObject.h"
#include <string>
#include "structs.h"

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
    double aX, aY;
public:
    static Level* levelP;
    static Camera* cameraP;
    Player(std::string tex);
    void SetAX(double acceleration);
    OBJRECT isTouchingMap(double x, double y, double w, double h);
    void Update() override;
    void Jump();
    void MoveCameraRoom();
    
    void DrawPlayer();
    void DrawPart(std::string tex, double angle, int x, int y);
};

