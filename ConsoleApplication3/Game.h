#pragma once

#include <vector>
#include <string>
#include "Camera.h"
#include "Textures.h"
#include "Level.h"
#include "Player.h"
#include "Input.h"

class GameObject;
class Textures;

class Game
{
private:
    bool running;
    std::vector<std::unique_ptr<GameObject>> objects;
    std::vector<std::unique_ptr<GameObject>> dyingObjects;
    std::vector<std::unique_ptr<GameObject>> pendingObjects;
    Camera camera;
    Textures textures;
    Level level;
    Player assy;
    Input input;
    SDL_Event event;
public:
    Game();
    void Run();
    void Update();
    void InitSystem();
    void LinkPointer(); 
    void Quit();
};

