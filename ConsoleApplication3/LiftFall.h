#pragma once
#include "GameObject.h"
class LiftFall :
    public GameObject
{
private:
    bool isFalling;
public:
    LiftFall(double X, double Y);
    void Update() override;
    void Stomped() override;
};

