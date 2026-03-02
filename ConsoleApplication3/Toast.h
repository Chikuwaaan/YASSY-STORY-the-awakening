#pragma once
#include "GameObject.h"
#include "Timer.h"

enum class PHASE {
    appear,
    stay,
    disappear
};

class Toast :
    public GameObject
{
private:
    PHASE phase;
    Timer timer;
    Timer star;

    std::u8string text;
public:
    Toast(std::u8string Text);
    void Update() override;
    void Draw() override;
};

