#include "CoinManager.h"
#include "Textures.h"

CoinManager::CoinManager() {
}

void CoinManager::Update() {
}

void CoinManager::Draw() {
    for (int i = 0; i < 3; i++) {
        texturesP->DrawSprite("coinmanager", { 48.0 + 96 * i,1032,96,96 }, { 16 * platformer::coin[i],0,16,16}, 0);
    }
    std::cout << platformer::coin[0] << platformer::coin[1] << platformer::coin[2] << std::endl;
}


void CoinManager::CollectCoin(int index) {
    platformer::coin[index] = 1;
}