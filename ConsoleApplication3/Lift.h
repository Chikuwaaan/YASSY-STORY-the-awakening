#pragma once
#include "GameObject.h"
class Lift :
    public GameObject
{
private:
    double posX, posY;
    double amplitudeX, amplitudeY;
    double vx0, vy0;
    double length;
public:
    Lift(double spawnX, double ampX, double velocityX, double spawnY, double ampY, double velocityY, double L, double H);
    void Update() override;
    void Draw() override;
};

