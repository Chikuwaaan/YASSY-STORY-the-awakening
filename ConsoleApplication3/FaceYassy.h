#pragma once
#include<vector>
#include<SDL.h>
#include <random>
#include "Button.h"
#include "UIManager.h"

class Input;
class Textures;
class Game;

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
    UIManager ui;
    static Input* inputP;
    static Textures* texturesP;
    static Game* gameP;

    FaceYassy();

    void Update();
    void Output();
    void RegisterButtons();
};

