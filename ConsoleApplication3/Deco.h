#pragma once
#include "GameObject.h"
class Deco :
    public GameObject
{
public:
    Deco(double X, double Y, double W, double H, double Layer, std::string tex);
};

