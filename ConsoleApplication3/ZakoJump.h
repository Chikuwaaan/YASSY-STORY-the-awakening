#pragma once
#include "GameObject.h"
#include "GameTimer.h"

class ZakoJump :
    public GameObject
{
private:
    GameTimer timer;
    double time;
public:
    ZakoJump(double X, double Y);
    void Update() override;
    void Draw() override;
    void Touched() override;
    void Stomped() override;
};

