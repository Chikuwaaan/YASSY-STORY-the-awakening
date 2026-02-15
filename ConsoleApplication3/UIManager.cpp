#include "UIManager.h"
#include "Input.h"
#include <SDL.h>

Input* UIManager::inputP = nullptr;

UIManager::UIManager() {
    buttons = {};

    currentLine = nullptr;
    currentButton = 0;
}

bool UIManager::Update() {
    IsCursorOnUI();
    for (auto& p : buttons) {
        p->Draw();

        if (currentLine && p == currentLine->selectables[currentButton]) {
            p->isSelected = true;
        }
        else {
            p->isSelected = false;
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
            if (currentLine->nextAction) {
                currentLine->nextAction();
                std::cout << "uo";
            }
            if (currentLine->next) {
                currentButton = 0;
                currentLine = currentLine->next;
            }
        }
        if (switchLine == -1) {
            if (currentLine->prevAction) {
                currentLine->prevAction();
                std::cout << "UO";
            }
            if (currentLine->prev) {
                currentButton = 0;
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

/*
* 選択カーソル
* 要素(ボタン)
* 要素の配置が縦か横か
* 双方向リスト
*/