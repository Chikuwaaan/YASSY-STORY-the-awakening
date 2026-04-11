#pragma once
#include "GameObject.h"
class CoinManager :
    public GameObject
{
private:
    std::vector<std::vector<bool>> progress;
public:
    CoinManager();
    void Update() override;
    void Draw() override;
    void Refresh();
    void CollectCoin(int index);
    std::vector<std::vector<bool>> GetProgress();
};

