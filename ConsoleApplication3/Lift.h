#pragma once
#include "GameObject.h"
class Lift :
    public GameObject
{
private:
    double posX, posY;
    int direction;
    double amplitude;
    double speed;
public:
    Lift(double spawnX, double spawnY, int initialDirection);
    void Update() override;
};

