#pragma once
#include "GameObject.h"
#include "GameTimer.h"
class Hosi :
    public GameObject
{
private:
    double angle;
    GameTimer timer;
public:
    Hosi(double X, double Y, double Angle);
    void Update() override;
    void Touched() override;
    void Stomped() override;
};

