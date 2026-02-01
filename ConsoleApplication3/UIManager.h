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
    void RenderUI();
    void AddButton(Button* ptr);
};

