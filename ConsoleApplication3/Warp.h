#pragma once
#include "GameObject.h"
#include "GameTimer.h"

class Warp :
    public GameObject
{
private:
    GameTimer timer;
    
    int index;
    bool on;
public:
    Warp* pair;
    GameTimer timerI;
    double interval;
    Warp(double X, double Y, int i);
    void Update() override;
    void Draw() override;
    void Touched() override;
    void Stomped() override;
};

