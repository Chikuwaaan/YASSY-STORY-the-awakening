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
        EVENT e = inputP->event;
        int switchLine = 0;
        int switchButton = 0;

        if (currentLine->direction == DIRECTION::H) {
            if (e.Right) switchButton = 1;
            if (e.Left) switchButton = -1;
            if (e.Up) switchLine = -1;
            if (e.Down) switchLine = 1;
        }
        else if (currentLine->direction == DIRECTION::V) {
            if (e.Right) switchLine = 1;
            if (e.Left) switchLine = -1;
            if (e.Up) switchButton = -1;
            if (e.Down) switchButton = 1;
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
            }
        }
        if (switchButton == -1) {
            currentButton--;
            if (currentButton < 0) {
                currentButton = (int)currentLine->selectables.size() - 1;
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

/*
* ‚¤‚¨‚¤‚¨w
* ‚¤‚¨‚¤‚¨w
* ‚¤‚¨‚¤‚¨‚¤‚¨www
*/