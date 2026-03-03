#pragma once
class GameTimer
{
private:
    double timer;
public:
    GameTimer();
    void Update();
    void Reset();
    double GetTime();
};

