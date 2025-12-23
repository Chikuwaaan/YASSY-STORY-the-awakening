#pragma once
#include "GameObject.h"
class Lift :
    public GameObject
{
private:
    double posX, posY;
    double amplitude;
public:
    Lift(double spawnX, double spawnY, double amp, double velocity);
    void Update() override;
};

