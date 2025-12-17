#pragma once

#include <vector>
#include <string>
#include "Camera.h"
#include "Textures.h"
#include "Level.h"
#include "Player.h"

class GameObject;
class Textures;

class Game
{
private:
    std::vector<std::unique_ptr<GameObject>> objects;
    std::vector<std::unique_ptr<GameObject>> dyingObjects;
    std::vector<std::unique_ptr<GameObject>> pendingObjects;
    Camera camera;
    Textures textures;
    Level level;
    Player assy;
public:
    Game();
    void InitSystem();
};

