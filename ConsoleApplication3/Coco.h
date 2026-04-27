#pragma once
#include "GameObject.h"

class Coco :
    public GameObject
{
private:
    bool falling;
public:
    Coco(double X, double Y);
    void Update() override;
    void Draw() override;
    void Touched() override;
    void Stomped() override;
};

