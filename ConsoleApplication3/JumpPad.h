#pragma once
#include "GameObject.h"
#include "GameTimer.h"
class JumpPad :
    public GameObject
{
private:
    GameTimer timer;
public:
    JumpPad(double X, double Y);
    void Update() override;
    void Touched() override;
    void Stomped() override;
    void Draw() override;
};

