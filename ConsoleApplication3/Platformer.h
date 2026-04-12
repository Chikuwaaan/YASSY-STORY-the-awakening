#pragma once
#include <vector>
#include <memory>
#include <utility>
#include <type_traits>
#include <iostream>
#include "Level.h"
#include "Player.h"
#include "Timer.h"
#include "CoinManager.h"
#include "GameObject.h"
#include <variant>

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
    CoinManager coinManager;

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
    void SaveProgress();

    void Init();
    void Spawn();
    void Quit();
    void Update();

    bool inScreen(std::unique_ptr<GameObject>& p);

    /*
    template<typename T, typename... Args>
    T* AddObject(Args&&... args) {
        std::unique_ptr p = std::make_unique<T>(std::forward<Args>(args)...);
        T* raw = p.get();
        pendingObjects.push_back(std::move(p));
        return raw;
    }
    */

    GameObject* AddObject(std::string objClass, std::vector<std::variant<double, std::string>> args);
};