#pragma once
#include "GameObject.h"
#include "GameTimer.h"
class Hossy :
    public GameObject
{
private:
    bool exproding;
    double angle;
    GameTimer timerSpin;
    GameTimer timerExprode;
public:
    Hossy(double X, double Y);
    void Update() override;
    void Draw() override;
    void Touched() override;
    void Stomped() override;
};

