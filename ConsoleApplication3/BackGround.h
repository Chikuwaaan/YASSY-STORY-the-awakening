#pragma once
#include "GameObject.h"
#include "Timer.h"

class BackGround :
    public GameObject
{
private:
    double x0, y0;
    double dx, dy;
    double camX0, camY0;
    double Mx, My;
    
    Timer timer;
public:
    BackGround(double X, double Y, double mulX, double mulY, double camX, double camY, double Layer, std::string tex);
    void Draw() override;
    void Update() override;
};

