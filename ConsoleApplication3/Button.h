#pragma once

#include <functional>

class Button
{
public:
    std::function<void()> action;
};

