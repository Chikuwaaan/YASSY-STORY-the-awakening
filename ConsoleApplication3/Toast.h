#pragma once
#include "GameObject.h"
#include "GameTimer.h"
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
    GameTimer timer;
    Timer star;

    std::u8string text;
public:
    Toast(std::u8string Text);
    void Update() override;
    void Draw() override;
};

