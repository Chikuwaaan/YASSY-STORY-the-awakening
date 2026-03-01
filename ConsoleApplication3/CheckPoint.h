#pragma once
#include "GameObject.h"
class CheckPoint :
    public GameObject
{
private:
    bool used;
public:
    CheckPoint(double x0, double y0);
    void Touched() override;
    void Stomped() override;
    void Draw() override;
};

