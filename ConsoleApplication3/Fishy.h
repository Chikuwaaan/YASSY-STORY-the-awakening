#pragma once
#include "GameObject.h"
class Fishy :
    public GameObject
{
private:
    double posX, amplitudeX, vx0;
public:
    Fishy(double X, double Y);
    void Update() override;
    void Draw() override;
    void Touched() override;
    void Stomped() override;
};