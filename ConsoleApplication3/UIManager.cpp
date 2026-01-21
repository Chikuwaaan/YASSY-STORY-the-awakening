#include "UIManager.h"
#include "UIElement.h"
#include <iostream>

UIManager::UIManager() {

}

void UIManager::Update() {
    for (auto& ui : UIs) {
        for (auto& element : ui) {
            element->Update();
        }
    }
}

void UIManager::MakeUI() {
    UIs.push_back({});
    UIs[0].push_back(std::make_unique<UIElement>(0,0));
}