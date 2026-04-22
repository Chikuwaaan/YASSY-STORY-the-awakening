#pragma once
#include "GameObject.h"
class Coco :
    public GameObject
{
public:
    Coco(double X, double Y);
    void Update() override;
};

