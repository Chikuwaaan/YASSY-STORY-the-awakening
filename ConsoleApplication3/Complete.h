#pragma once
#include "Button.h"
#include "UIManager.h"
#include "Timer.h"
#include "GameTimer.h"

class Textures;

class Complete
{
private:
    Timer bgTimer;
    GameTimer textTimer;

    UIManager ui;
    LINE line;
    Button next;

    double clearTime;
    double bestTime;
    int deaths;
    std::vector<double> y;
    std::vector<double> targetY;
    
public:
    static Textures* texturesP;

    std::u8string levelName;
    bool finish;

    Complete();
    void Update();
    void SetClearTime(double time);
    void SetBestTime(double time);
    void SetDeaths(int n);
};

