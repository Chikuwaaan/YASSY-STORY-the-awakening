#pragma once
#include<vector>
#include<SDL.h>
#include <random>
#include "Button.h"

class Input;
class Textures;
class UIManager;

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

    Button test;

    void Delete();
public:
    static Input* inputP;
    static Textures* texturesP;
    static UIManager* uiP;

    FaceYassy();

    void Update();
    void Output();
    void RegisterButtons();
};

