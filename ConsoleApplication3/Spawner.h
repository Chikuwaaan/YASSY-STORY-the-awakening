#pragma once
#include "GameObject.h"
#include "GameTimer.h"
#include <vector>
#include <variant>

class Spawner :
    public GameObject
{
private:
    std::string Class;
    std::vector<std::variant<double, std::string>> args;
    GameTimer timer;
    double interval;
public:
    Spawner(std::string tex, std::vector<std::variant<double, std::string>> Args);
    void Update() override;
};