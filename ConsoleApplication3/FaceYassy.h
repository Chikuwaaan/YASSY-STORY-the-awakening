#pragma once
#include<vector>
#include<SDL.h>
#include <random>

class Input;
class Textures;

class FaceYassy
{
private:
    std::vector<std::vector<SDL_Point>> trajectories;
    std::vector<std::vector<SDL_Point>> trajectoriesModded;
    int layer;
    int grabx, graby;
    int mousedx, mousedy;

    std::random_device rd;
    std::mt19937 gen;
public:
    static Input* inputP;
    static Textures* texturesP;

    FaceYassy();
    void Update();
};

