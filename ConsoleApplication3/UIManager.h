#pragma once
#include <vector>
#include <iostream>
#include "UIElement.h"


class UIManager
{
private:
    std::vector<std::unique_ptr<UIElement>> UIs;
public:
    UIManager();
    void Update();
    void MakeUI();
};

