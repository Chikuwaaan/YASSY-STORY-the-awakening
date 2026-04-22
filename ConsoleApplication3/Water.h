#pragma once
#include "GameObject.h"
class Water :
    public GameObject
{
public:
    Water(double X, double Y, double W, double H);
    void Touched() override;
    void Stomped() override;
};

