#pragma once
#include <vector>
#include <iostream>
#include "Button.h"


class UIManager
{
private:
    std::vector<Button*> buttons;
public:
    UIManager();
    void Update();
    void AddButton(Button* ptr);
    bool IsCursorOnUI();
};

