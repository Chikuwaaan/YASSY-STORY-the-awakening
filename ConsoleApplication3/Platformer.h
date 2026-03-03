#pragma once
#include <vector>
#include <memory>
#include <utility>
#include <type_traits>
#include <iostream>
#include "Level.h"
#include "Player.h"
#include "Timer.h"

class GameObject;
class Textures;
class Camera;
class Input;
class Sounds;

struct LEVELINFO {
    std::u8string name;
    std::string BGM;
};


class Platformer {
private:
    Level level;
    Player player;

    bool editorMode;

    LEVELINFO info;

    Timer timer;
public:
    static Textures* texturesP;
    static Camera* cameraP;
    static Input* inputP;
    static Sounds* soundsP;

    std::vector<std::unique_ptr<GameObject>> objects;
    std::vector<std::unique_ptr<GameObject>> dyingObjects;
    std::vector<std::unique_ptr<GameObject>> pendingObjects;

    Platformer();

    void LoadLevelInfo();
    void LoadEntities();

    void Init();
    void Quit();
    void Update();
    bool inScreen(std::unique_ptr<GameObject>& p);

    template<typename T, typename... Args>
    void AddObject(Args&&... args) {
        pendingObjects.push_back(
            std::make_unique<T>(std::forward<Args>(args)...)
        );
    }
};