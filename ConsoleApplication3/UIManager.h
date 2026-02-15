#pragma once
#include <vector>
#include <iostream>
#include "Button.h"

enum DIRECTION {
    H,
    V
};
struct LINE {
    std::vector<Button*> selectables;
    DIRECTION direction;
    LINE* prev;
    LINE* next;
};

class UIManager
{
private:
    
    std::vector<LINE*> elements;
public:
    std::vector<Button*> buttons;

    UIManager();
    bool Update();
    void AddButton(Button* ptr);
    void AddLine(LINE* line);
    bool IsCursorOnUI();
};

