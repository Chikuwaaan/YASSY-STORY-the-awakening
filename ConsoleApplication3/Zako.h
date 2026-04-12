#pragma once
#include "GameObject.h"
class Zako :
    public GameObject
{
private:
    int direction = -1;
public:
    Zako(double x0, double y0);
    void Update() override;
    //void Draw() override;
    void Touched() override;
    void Stomped() override;
};

