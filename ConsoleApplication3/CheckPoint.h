#pragma once
#include "GameObject.h"
class CheckPoint :
    public GameObject
{
private:
    bool used;
    int index;
public:
    CheckPoint(double x0, double y0, double Index);
    void Update() override;
    void Touched() override;
    void Stomped() override;
    void Draw() override;
};

