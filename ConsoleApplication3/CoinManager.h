#pragma once
#include "GameObject.h"
class CoinManager :
    public GameObject
{
private:
    bool arr[3];
public:
    CoinManager();
    void Update() override;
    void Draw() override;
    void CollectCoin(int index);
};

