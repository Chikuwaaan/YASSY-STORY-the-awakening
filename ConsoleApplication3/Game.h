#pragma once

#include <vector>
#include <string>
#include "Camera.h"
#include "Textures.h"
#include "Level.h"
#include "Player.h"
#include "Input.h"
#include "ScreenShot.h"
#include "OverLay.h"
#include "BackGround.h"

class GameObject;
class Textures;



class Game
{
private:
    bool running;
    
    std::vector<std::unique_ptr<GameObject>> dyingObjects;
    std::vector<std::unique_ptr<GameObject>> pendingObjects;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Textures> textures;
    std::unique_ptr<Level> level;
    std::unique_ptr<Player> assy;
    std::unique_ptr<Input> input;
    std::unique_ptr<ScreenShot> screenshot;
    std::unique_ptr<OverLay> overlay;
    std::unique_ptr<BackGround> background;
    //Level level;
    //Player assy;
    //Input input;
public:
    std::vector<std::unique_ptr<GameObject>> objects;

    Game();
    void SetupEntities();
    void Run();
    void HandleEvent();
    void Update();
    void InitSystem();
    void MakeInstance(); 
    void Quit();
};

