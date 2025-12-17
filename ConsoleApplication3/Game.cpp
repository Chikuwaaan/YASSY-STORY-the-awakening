#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <windows.h>
#include "Game.h"
#include "namespace.h"
#include "GameObject.h"

Game::Game() {
    running = true;
    LinkPointer();
}

void Game::Run() {
    double accumulator = 0.0;
    double lastTime = SDL_GetTicks() / 1000.0;
    while (running) {
        double currentTime = SDL_GetTicks() / 1000.0;
        double frameTime = currentTime - lastTime;
        lastTime = currentTime;
        accumulator += frameTime;

        while (accumulator >= settings::dt) {
            while (SDL_PollEvent(&event));
            input.GetKey();
            Update();
            accumulator -= settings::dt;
        }
    }
}

void Game::Update() {
    SDL_SetRenderDrawColor(settings::renderer, 117, 226, 255, 255);
    SDL_Rect rect = { 0, 0, settings::baseW, settings::baseH };
    SDL_RenderFillRect(settings::renderer, &rect);
    //SDL_RenderCopy(settings::renderer, IMG_LoadTexture(settings::renderer, "Assets/textures/assy.png"), NULL, &rect);

    for (auto& obj : objects) {
        obj->Update();
    }
    assy.Update();

    for (auto& p : pendingObjects) {
        objects.push_back(std::move(p));
    }
    pendingObjects.clear();

    level.DrawMap();
    for (auto& obj : objects) {
        obj->Draw();
    }
    assy.DrawPlayer();
    textures.Update();
    camera.Update();

    SDL_RenderPresent(settings::renderer);
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
    //Mix_Music* music = Mix_LoadMUS("Assets/audio/sanctuary.wav");
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

    textures.LoadTextures();
}


void Game::LinkPointer() {


    Camera::texturesP = &textures;
    Textures::cameraP = &camera;
    Level::texturesP = &textures;
    Player::levelP = &level;
    Player::cameraP = &camera;
    GameObject::texturesP = &textures;
    GameObject::cameraP = &camera;
}

void Game::Quit() {
    SDL_DestroyWindow(settings::window);
    SDL_Quit();
}