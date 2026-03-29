#pragma once
#include "GameObject.h"
class Goal :
    public GameObject
{
private:
public:
    Goal(double X, double Y, double W, double H);
    void Touched() override;
    void Stomped() override;
};

