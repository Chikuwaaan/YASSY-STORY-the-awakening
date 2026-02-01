#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <windows.h>
#include "Game.h"
#include "namespace.h"
#include "GameObject.h"

#include "Lift.h"
#include "Zako.h"
#include "Spikes.h"
#include "CheckPoint.h"
#include "UIManager.h"
#include "UIElement.h"
#include "FaceYassy.h"
#include "Button.h"

Game::Game() {
    running = true;
    scene = Scene::Platformer;
}

void Game::ChangeScene(Scene s) {
    scene = s;
    if (s == Scene::Platformer) {
        int levelN = platformer::level;
        level->LoadLevel(levelN);
        camera->LoadCameraRoom(levelN);
        assy->SetSpawnPoint(400, 600);
        assy->Spawn();

        
        Mix_Music* music = Mix_LoadMUS("Assets/sounds/6.ogg");
        Mix_PlayMusic(music, -1);
    }
}

void Game::SetupEntities() {
    objects.clear();
    pendingObjects.push_back(std::make_unique<CheckPoint>());
}

void Game::Run() {
    //ChangeScene(Scene::Platformer);
    ChangeScene(Scene::FaceYassy);
    faceyassy->Unco();

    double accumulator = 0.0;
    double lastTime = SDL_GetTicks() / 1000.0;

    while (running) {
        double currentTime = SDL_GetTicks() / 1000.0;
        double frameTime = currentTime - lastTime;
        lastTime = currentTime;
        if (frameTime > 0.1) frameTime = 0.1;
        settings::timeScale = frameTime * settings::multiplier;
            
        HandleEvent();
        Update();
        //textures->DrawTexts(std::to_string(Mix_GetMusicPosition(NULL)), { 0,0,0,255 }, { 0,50,1,1 }, 0, {});

        const Uint8* keystate = input->keystate;
        const EVENT event = input->event;

        if (event.ESCAPE) {
            running = 0;
            if (scene == Scene::Platformer) {
                level->FileOutput(platformer::level);
            }
            if (scene == Scene::FaceYassy) {
                faceyassy->Output();
            }
        }
        if (event.F12) {
            screenshot->SaveScreenShot();
        }
        accumulator -= settings::dt;

        SDL_RenderPresent(settings::renderer);
    }
}

void Game::HandleEvent() {
    input->GetKey();
    input->GetCursor();
    input->GetEvent();
}

void Game::Update() {
    if (scene == Scene::Platformer) {
        platformer::flames++;

        CAMERA cam = camera->GetCam();
        OBJRECT screenRect = { 0, 0, (double)settings::baseW, (double)settings::baseH, 1 };
        textures->DrawRect({ 255,255,255,255 }, screenRect, 0);
        background->Draw();

        //UPDATE
        for (auto& obj : objects) {
            obj->Update();
        }
        assy->Update();
        textures->Update();

        for (auto& p : pendingObjects) {
            objects.push_back(std::move(p));
        }
        pendingObjects.clear();

        for (auto& obj : objects) {
            obj->Draw();
        }
        level->DrawMap();
        assy->DrawPlayer();
        textures->Update();
        camera->Update();

        objects.erase(
            std::remove_if(objects.begin(), objects.end(),
                [](const std::unique_ptr<GameObject>& o)
                {return o->IsDead(); }),
            objects.end()
        );

        level->Editor();

        overlay->Update();
        textures->DrawImage("assy2", { 100, 980, 100, 100 }, 0, { 1, (double)platformer::flames });
    }

    if (scene == Scene::FaceYassy) {
        faceyassy->Update();
        ui->RenderUI();
    }
}

void Game::InitSystem() {
    SetProcessDPIAware();
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    
    SDL_Surface* surface = IMG_Load("Assets/textures/assy.png");
    SDL_Cursor* cursor = SDL_CreateColorCursor(surface, 0, 0);
    SDL_SetCursor(cursor);
    SDL_FreeSurface(surface);
    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    

    //Open Window
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
    float scaleX = (float)dm.w / settings::baseW;
    float scaleY = (float)dm.h / settings::baseH;
    float scale = (scaleX < scaleY) ? scaleX : scaleY;
    int winW = (int)(settings::baseW * scale);
    int winH = (int)(settings::baseH * scale);
    settings::window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winW, winH, SDL_WINDOW_FULLSCREEN_DESKTOP);
    //settings::window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, 0);
    settings::renderer = SDL_CreateRenderer(settings::window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //| SDL_RENDERER_PRESENTVSYNC
    SDL_RenderSetLogicalSize(settings::renderer, settings::baseW, settings::baseH);

    SDL_DisplayMode disp;
    SDL_GetDesktopDisplayMode(0, &disp);
    std::cout << "[DEBUG]リフレッシュレート：" << disp.refresh_rate << std::endl;
}


void Game::MakeInstance() {
    camera = std::make_unique<Camera>();
    textures = std::make_unique<Textures>();
    sounds = std::make_unique<Sounds>();
    level = std::make_unique<Level>();
    assy = std::make_unique<Player>();
    input = std::make_unique<Input>();
    screenshot = std::make_unique<ScreenShot>();
    overlay = std::make_unique<OverLay>();
    background = std::make_unique<BackGround>();
    faceyassy = std::make_unique<FaceYassy>();
    ui = std::make_unique<UIManager>();

    Camera::texturesP = textures.get();
    Camera::inputP = input.get();
    Textures::cameraP = camera.get();
    Level::texturesP = textures.get();
    Level::inputP = input.get();
    Level::cameraP = camera.get();
    Level::gameP = this;
    Player::gameP = this;
    Player::levelP = level.get();
    Player::cameraP = camera.get();
    Player::overlayP = overlay.get();
    GameObject::texturesP = textures.get();
    GameObject::soundsP = sounds.get();
    GameObject::cameraP = camera.get();
    GameObject::inputP = input.get();
    GameObject::levelP = level.get();
    GameObject::playerP = assy.get();
    OverLay::texturesP = textures.get();
    OverLay::playerP = assy.get();
    FaceYassy::inputP = input.get();
    FaceYassy::texturesP = textures.get();
    FaceYassy::uiP = ui.get();
    Button::texturesP = textures.get();
}

void Game::Quit() {
    SDL_DestroyWindow(settings::window);
    SDL_Quit();
}