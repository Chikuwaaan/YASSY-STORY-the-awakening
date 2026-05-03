#include "UIManager.h"
#include "Input.h"
#include <SDL.h>

Input* UIManager::inputP = nullptr;

UIManager::UIManager() {
    lines = {};

    currentLine = nullptr;
    currentButton = 0;
}

bool UIManager::Update() {
    IsCursorOnUI();
    for (auto& l : lines) {
        for (auto& b : l->selectables) {
            b->Draw();
            if (currentLine && b == currentLine->selectables[currentButton]) {
                b->isSelected = true;
            }
            else {
                b->isSelected = false;
            }
        }
    }

    if (currentLine) {
        int switchLine = 0;
        int switchButton = 0;

        if (currentLine->direction == DIRECTION::H) {
            if (inputP->GetEvent(Event::Right)) switchButton = 1;
            if (inputP->GetEvent(Event::Left)) switchButton = -1;
            if (inputP->GetEvent(Event::Up)) switchLine = -1;
            if (inputP->GetEvent(Event::Down)) switchLine = 1;
        }
        else if (currentLine->direction == DIRECTION::V) {
            if (inputP->GetEvent(Event::Right)) switchLine = 1;
            if (inputP->GetEvent(Event::Left)) switchLine = -1;
            if (inputP->GetEvent(Event::Up)) switchButton = -1;
            if (inputP->GetEvent(Event::Down)) switchButton = 1;
        }


        if (switchLine == 1) {
            if (currentLine->next) {
                currentButton = 0;
                if (currentLine->nextAction) {
                    currentLine->nextAction();
                }
                currentLine = currentLine->next;
            }
            
        }
        if (switchLine == -1) {
            if (currentLine->prev) {
                currentButton = 0;
                if (currentLine->prevAction) {
                    currentLine->prevAction();
                }
                currentLine = currentLine->prev;
            }
            
        }

        if (switchButton == 1) {
            currentButton++;
            if (currentButton >= (int)currentLine->selectables.size()) {
                currentButton = 0;
                if (currentLine->endAction) {
                    currentLine->endAction();
                }
            }
        }
        if (switchButton == -1) {
            currentButton--;
            if (currentButton < 0) {
                currentButton = (int)currentLine->selectables.size() - 1;
                if (currentLine->beginAction) {
                    currentLine->beginAction();
                }
            }
        }
    }
    
    for (auto& l : lines) {
        for (auto& b : l->selectables) {
            if (b->CheckPressed()) {
                return 1;
            }
        }
    }

    return 0;
}

void UIManager::AddLine(LINE* line) {
    lines.push_back(line);
}

bool UIManager::IsCursorOnUI() {
    for (auto& l : lines) {
        for (auto& b : l->selectables) {
            if (b->CheckOnMouse()) {
                return 1;
            }
        }
    }

    return 0;
}

void UIManager::ChangeCurrentButton(int index) {
    currentButton += index;
    if (currentButton < 0) {
        currentButton = 0;
    }
    else if (currentButton > currentLine->selectables.size()-1) {
        currentButton = currentLine->selectables.size()-1;
    }
}