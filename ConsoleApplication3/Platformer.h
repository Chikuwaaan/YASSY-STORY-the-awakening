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
#include "Pause.h"
#include <variant>

class Textures;
class Camera;
class Input;
class Sounds;
class Save;
class Game;

struct LEVELINFO {
    std::u8string name;
    std::string BGM;
};


class Platformer {
private:
    Level level;
    Player player;
    CoinManager coinManager;
    Pause pause;

    bool pausing;
    bool editorMode;
    bool completed;

    LEVELINFO info;

    Timer timer;

public:
    static Textures* texturesP;
    static Camera* cameraP;
    static Input* inputP;
    static Sounds* soundsP;
    static Save* saveP;
    static Game* gameP;

    std::vector<std::unique_ptr<GameObject>> objects;
    std::vector<std::unique_ptr<GameObject>> dyingObjects;
    std::vector<std::unique_ptr<GameObject>> pendingObjects;

    Platformer();

    void LoadLevelInfo();
    void LoadEntities();

    void Init();
    void Spawn();
    void Complete();
    void Save();
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