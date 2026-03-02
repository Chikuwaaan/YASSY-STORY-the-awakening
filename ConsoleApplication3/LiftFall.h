#pragma once
#include "GameObject.h"
#include "Timer.h"

class LiftFall :
    public GameObject
{
private:
    double x0, y0;
    double length;
    bool isFalling;
    Timer timer;
    bool respawning;
public:
    LiftFall(double X, double Y, double L);
    void Update() override;
    void Stomped() override;
    void Draw() override;
};

