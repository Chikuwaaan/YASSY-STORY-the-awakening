#pragma once
#include <vector>
#include <memory>
#include <utility>
#include <type_traits>
#include <iostream>
#include "Level.h"
#include "Player.h"
#include "BackGround.h"

class GameObject;
class Textures;
class Camera;

class Platformer {
private:
    Level level;
    Player player;
    BackGround background;
public:
    static Textures* texturesP;
    static Camera* cameraP;

    std::vector<std::unique_ptr<GameObject>> objects;
    std::vector<std::unique_ptr<GameObject>> dyingObjects;
    std::vector<std::unique_ptr<GameObject>> pendingObjects;

    Platformer();

    void LoadEntities();

    void Init();
    void Quit();
    void Update();

    template<typename T, typename... Args>
    void AddObject(Args&&... args) {
        pendingObjects.push_back(
            std::make_unique<T>(std::forward<Args>(args)...)
        );
    }
};