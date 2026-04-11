#pragma once
#include "GameObject.h"
#include "Timer.h"
#include "GameTimer.h"
#include "Rand.h"

class CoinManager;

class Coin :
    public GameObject
{
private:
    Timer timer;
    GameTimer GameTimer;
    Rand random;
    int index;
    bool isCollected;
    bool anim;
public:
    static CoinManager* managerP;

    Coin(double X, double Y, double Index);
    void Update() override;
    void Draw() override;
    void Touched() override;
    void Stomped() override;
};


