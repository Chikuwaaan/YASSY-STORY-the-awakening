#pragma once
#include "GameObject.h"
#include "GameTimer.h"


class Spawner :
    public GameObject
{
private:
    GameTimer timer;
public:
    Spawner(double X, double Y);
    void Update() override;
};