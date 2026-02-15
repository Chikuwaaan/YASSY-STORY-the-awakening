#pragma once
#include <vector>
#include <iostream>
#include <functional>
#include "Button.h"

class Input;

enum DIRECTION {
    H,
    V
};
struct LINE {
    std::vector<Button*> selectables;
    DIRECTION direction;
    LINE* prev;
    LINE* next;
    std::function<void()> prevAction;
    std::function<void()> nextAction;
};

class UIManager
{
private:
    
public:
    static Input* inputP;

    std::vector<Button*> buttons;

    LINE* currentLine;
    int currentButton;
    

    UIManager();
    bool Update();
    void AddButton(Button* ptr);
    bool IsCursorOnUI();
};

