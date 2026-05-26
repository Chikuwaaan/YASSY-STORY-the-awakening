#pragma once
#include "GameObject.h"
#include "GameTimer.h"
class Fan :
    public GameObject
{
private:
    GameTimer timer1;
    int direction;
public:
    Fan(double X, double Y, double Direction);
    void Update() override;
    void Touched();
    void Stomped();
    void Draw() override;
};

