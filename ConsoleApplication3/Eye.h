#pragma once
#include "GameObject.h"
#include "Rand.h"

class Eye :
    public GameObject
{
private:
    Rand random;

    double r;

public:
    double irisX;
    double irisY;
    double irisVX;
    double irisVY;
    double theta;
    double angle;
    double incident;

    Eye(double R);
    void Update(double AX, double AY);
    void Draw() override;
};

