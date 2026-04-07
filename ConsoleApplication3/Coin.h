#pragma once
#include "GameObject.h"
#include "Timer.h"

class CoinManager;

class Coin :
    public GameObject
{
private:
    Timer timer;
    int index;
public:
    static CoinManager* managerP;

    Coin(double X, double Y, double Index);
    void Draw() override;
    void Touched() override;
    void Stomped() override;
};


