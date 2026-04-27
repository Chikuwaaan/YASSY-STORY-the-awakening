#pragma once
#include "GameObject.h"
class Fishy :
    public GameObject
{
private:
    double posX, amplitudeX, vx0;
    double y0;
    int type;
public:
    Fishy(double X, double Y, double Type);
    void Update() override;
    void Draw() override;
    void Touched() override;
    void Stomped() override;
};