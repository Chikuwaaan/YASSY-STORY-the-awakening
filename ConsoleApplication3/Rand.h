#pragma once
#include <iostream>
#include <random>
class Rand
{
private:
    std::mt19937 gen;
public:
    Rand();
    int random(int min, int max);
    double frandom(double min, double max);
};

