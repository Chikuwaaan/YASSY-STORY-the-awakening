#pragma once
#include "GameObject.h"
#include "Rand.h"

class Tomato :
    public GameObject
{
private:
    Rand random;
public:
    Tomato(double X, double Y);
    void Update() override;
    void Draw() override;
};

