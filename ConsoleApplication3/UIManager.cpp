#include "UIManager.h"

UIManager::UIManager() {
    buttons = {};
}

bool UIManager::Update() {
    IsCursorOnUI();
    for (auto& p : buttons) {
        p->Draw();
    }
    for (auto& p : buttons) {
        if (p->CheckPressed()) {
            return 1;
        }
    }
    return 0;
}

void UIManager::AddButton(Button* ptr) {
    buttons.push_back(ptr);
}

bool UIManager::IsCursorOnUI() {
    for (auto& p : buttons) {
        if (p->CheckOnMouse()) {
            return 1;
        }
    }
    return 0;
}