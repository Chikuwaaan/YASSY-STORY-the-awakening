#include "UIManager.h"

UIManager::UIManager() {
    buttons = {};
}

void UIManager::RenderUI() {
    for (auto& p : buttons) {
        p->Draw();
    }
}

void UIManager::AddButton(Button* ptr) {
    buttons.push_back(ptr);
}