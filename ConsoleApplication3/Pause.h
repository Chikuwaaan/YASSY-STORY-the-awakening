#pragma once
#include "Button.h"
#include "UIManager.h"
#include "Options.h"
#include <functional>

class Pause
{
private:
    Options options;
public:
    std::function<void()> back;
    Pause();
    void Update();
    void SetBackButton();
};

