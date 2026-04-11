#include "CoinManager.h"
#include "Textures.h"

CoinManager::CoinManager() {
    progress = {
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0}
    };
}

void CoinManager::Update() {
}

void CoinManager::Draw() {
    for (int i = 0; i < 3; i++) {
        texturesP->DrawSprite("coinmanager", { 48.0 + 96 * i,1032,96,96 }, { 16 * progress[platformer::level-1][i],0,16,16 }, 0);
    }
}

void CoinManager::Refresh() {
    progress = savedata::coin;
}

void CoinManager::CollectCoin(int index) {
    progress[platformer::level-1][index] = 1;
}

std::vector<std::vector<bool>> CoinManager::GetProgress() {
    return progress;
}