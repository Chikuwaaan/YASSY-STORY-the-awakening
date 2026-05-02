#pragma once
#include "GameObject.h"
#include "Timer.h"
#include "Rand.h"

enum class particle {
    splash,
    mud,
    assy
};

struct point {
    double x;
    double y;
    double span;
    double v;
    double angle;
};

class Particle :
    public GameObject
{
private:
    Rand random;
    Timer timer;
    particle type;
    std::vector<point> vector;
public:
    Particle(double X, double Y, std::string Type);
    void Update() override;
    void Draw() override;
};

