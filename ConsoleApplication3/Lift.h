#pragma once
#include "GameObject.h"
class Lift :
    public GameObject
{
private:
    double posX, posY;
    double amplitudeX, amplitudeY;
public:
    Lift(double spawnX, double ampX, double velocityX, double spawnY, double ampY, double velocityY);
    void Update() override;
};

