#pragma once
#include "GameObject.h"
class CheckPoint :
    public GameObject
{
public:
    CheckPoint();
    void Touched() override;
    void Update() override;
};

