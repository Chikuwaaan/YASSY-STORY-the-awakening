#pragma once
#include "GameObject.h"
class Zako :
    public GameObject
{
public:
    Zako();
    void Update() override;
    void Damage() override;
};

