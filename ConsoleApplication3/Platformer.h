#pragma once
#include <vector>
#include "Level.h"
#include "Player.h"

class GameObject;
class Textures;
class Camera;

class Platformer {
private:
    Level level;
    Player player;
public:
    static Textures* texturesP;
    static Camera* cameraP;

    std::vector<GameObject> objects;
    std::vector<GameObject> dyingObjects;
    std::vector<GameObject> pendingObjects;

    Platformer();
    void Init();
    void Quit();
    void Update();
};