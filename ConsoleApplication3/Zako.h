#pragma once
#include "GameObject.h"
class Zako :
    public GameObject
{
public:
    Zako(double x0, double y0);
    void Update() override;
    void Damage() override;
};

