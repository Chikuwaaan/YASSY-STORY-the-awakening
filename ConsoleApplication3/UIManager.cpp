#include "UIManager.h"

UIManager::UIManager() {
    buttons = {};
}

void UIManager::Update() {
    for (auto& p : buttons) {
        p->CheckPressed();
        p->Draw();
    }
}

void UIManager::AddButton(Button* ptr) {
    buttons.push_back(ptr);
}

bool UIManager::IsCursorOnUI() {
    for (auto& p : buttons) {
        if (p->OnMouse()) {
            return 1;
        }
    }
    return 0;
}