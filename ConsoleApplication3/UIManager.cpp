#include "UIManager.h"
#include "UIElement.h"
#include <iostream>

UIManager::UIManager() {

}

void UIManager::Update() {
    for (auto& ui : UIs) {
        ui->Update();
    }
}

void UIManager::MakeUI() {
    UIs.push_back(std::make_unique<UIElement>(0, 0));
}