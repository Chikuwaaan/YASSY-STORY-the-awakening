#pragma once

#include <vector>
#include <string>
#include "Camera.h"
#include "Textures.h"
#include "Sounds.h"
#include "Input.h"
#include "ScreenShot.h"
#include "OverLay.h"
#include "BackGround.h"
#include "UIManager.h"
#include "FaceYassy.h"
#include "Button.h"
#include "Title.h"
#include "Platformer.h"
#include "LevelSelect.h"
#include "Save.h"
#include "Timer.h"

class GameObject;
class Textures;
class UIManager;

enum class Scene {
    Loading,
    Title,
    Platformer,
    FaceYassy,
    SlotSelect,
    LevelSelect
};

class Game
{
private:
    bool running;
    Scene scene;
    Scene sceneReserve;
    Timer timer;

    std::vector<std::unique_ptr<GameObject>> dyingObjects;
    std::vector<std::unique_ptr<GameObject>> pendingObjects;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Textures> textures;
    std::unique_ptr<Sounds> sounds;
    std::unique_ptr<Input> input;
    std::unique_ptr<ScreenShot> screenshot;
    std::unique_ptr<OverLay> overlay;
    std::unique_ptr<BackGround> background;
    std::unique_ptr<FaceYassy> faceyassy;
    std::unique_ptr<Title> title;
    std::unique_ptr<Platformer> platformer;
    std::unique_ptr<LevelSelect> levelselect;
    std::unique_ptr<Save> save;

    void SceneChanging();
public:
    std::vector<std::unique_ptr<GameObject>> objects;

    Game();
    void ChangeScene(Scene s);
    void Run();
    void Update();
    void InitSystem();
    void MakeInstance(); 
    void ExitGame();
    void Quit();
};

