#pragma once
#include "GameObject.h"
class CoinManager :
    public GameObject
{
public:
    CoinManager();
    void Update() override;
    void Draw() override;
    void CollectCoin(int index);
};

