#pragma once
#include "GameObject.h"
class Level;

class Spikes :
    public GameObject
{
public:
    Spikes(double x, double y, int direction, int length);
};

