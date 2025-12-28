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
#include "ScreenShot.h"

Game::Game() {
    running = true;
}

void Game::Run() {
    MakeInstance();

    pendingObjects.push_back(std::make_unique<Lift>(1500, 200, 200, 300, 0, 0));
    pendingObjects.push_back(std::make_unique<Lift>(2500, 200, -200, 400, 0, 0));
    pendingObjects.push_back(std::make_unique<Lift>(3500, 0, 0, 500, 300, 300));

    double accumulator = 0.0;
    double lastTime = SDL_GetTicks() / 1000.0;
    while (running) {
        double currentTime = SDL_GetTicks() / 1000.0;
        double frameTime = currentTime - lastTime;
        lastTime = currentTime;
        accumulator += frameTime;

        while (accumulator >= settings::dt) {
            HandleEvent();
            Update();
            const Uint8* keystate = input->keystate;
            const SDL_Event event = input->event;
            if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    level->FileOutput();
                    running = 0;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_F12) {
                    screenshot->SaveScreenShot();
                }
            }

            accumulator -= settings::dt;
        }
    }
}

void Game::HandleEvent() {
    input->GetKey();
    SDL_PollEvent(&(input->event));
}

void Game::Update() {
    platformer::flames++;

    SDL_SetRenderDrawColor(settings::renderer, 117, 226, 255, 255);
    SDL_Rect rect = { 0, 0, settings::baseW, settings::baseH };
    SDL_RenderFillRect(settings::renderer, &rect);
    //SDL_RenderCopy(settings::renderer, IMG_LoadTexture(settings::renderer, "Assets/textures/assy.png"), NULL, &rect);

    for (auto& obj : objects) {
        obj->Update();
    }
    assy->Update();

    for (auto& p : pendingObjects) {
        objects.push_back(std::move(p));
    }
    pendingObjects.clear();
    
    
    
    for (auto& obj : objects) {
        obj->Draw();
    }
    level->DrawMap();
    assy->Draw();
    assy->DrawPlayer();
    textures->Update();
    camera->Update();
    
    objects.erase(
        std::remove_if(objects.begin(), objects.end(),
            [](const std::unique_ptr<GameObject>& o)
            {return o->IsDead(); }),
        objects.end()
    );

    SDL_RenderPresent(settings::renderer);

    
}

void Game::InitSystem() {
    SetProcessDPIAware();
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    /*
    SDL_Surface* surface = IMG_Load("Assets/textures/assy.png");
    SDL_Cursor* cursor = SDL_CreateColorCursor(surface, 0, 0);
    SDL_SetCursor(cursor);
    SDL_FreeSurface(surface);
    */

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    //Mix_Music* music = Mix_LoadMUS("Assets/sounds/ending.mp3");
    //Mix_PlayMusic(music, -1);

    //Open Window
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
    float scaleX = (float)dm.w / settings::baseW;
    float scaleY = (float)dm.h / settings::baseH;
    float scale = (scaleX < scaleY) ? scaleX : scaleY;
    int winW = (int)(settings::baseW * scale);
    int winH = (int)(settings::baseH * scale);
    settings::window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winW, winH, SDL_WINDOW_FULLSCREEN_DESKTOP);
    settings::renderer = SDL_CreateRenderer(settings::window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(settings::renderer, settings::baseW, settings::baseH);

}


void Game::MakeInstance() {
    camera = std::make_unique<Camera>();
    textures = std::make_unique<Textures>();
    level = std::make_unique<Level>();
    assy = std::make_unique<Player>();
    input = std::make_unique<Input>();
    screenshot = std::make_unique<ScreenShot>();

    Camera::texturesP = textures.get();
    Camera::inputP = input.get();
    Textures::cameraP = camera.get();
    Level::texturesP = textures.get();
    Player::gameP = this;
    Player::levelP = level.get();
    Player::cameraP = camera.get();
    GameObject::texturesP = textures.get();
    GameObject::cameraP = camera.get();
    GameObject::inputP = input.get();
}

void Game::Quit() {
    SDL_DestroyWindow(settings::window);
    SDL_Quit();
}