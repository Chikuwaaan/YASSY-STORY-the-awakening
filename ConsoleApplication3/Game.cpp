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
#include "UIManager.h"
#include "UIElement.h"
#include "FaceYassy.h"
#include "Button.h"

Game::Game() 
{
    running = true;
    scene = Scene::Platformer;
}

/*リセットしないインスタンス↓
* camera
* textures
* sounds
* input
* screenshot
* overlay
*/
void Game::ChangeScene(Scene s) {
    background.reset();
    faceyassy.reset();
    title.reset();
    platformer.reset();
    levelselect.reset();

    scene = s;
    if (s == Scene::Title) {
        title = std::make_unique<Title>();

        title->Init();
    }
    if (s == Scene::Platformer) {
        platformer = std::make_unique<Platformer>();
        GameObject::platformerP = platformer.get();

        platformer->Init();

        int levelN = platformer::level;
        camera->LoadCameraRoom(levelN);
        camera->Init();
        
        /*
        Mix_Music* music = Mix_LoadMUS("Assets/sounds/6.ogg");
        Mix_PlayMusic(music, -1);
        */
    }

    if (s == Scene::FaceYassy) {
        faceyassy = std::make_unique<FaceYassy>();
        Mix_HaltMusic();
        faceyassy->RegisterButtons();
    }

    if (s == Scene::LevelSelect) {
        levelselect = std::make_unique<LevelSelect>();
    }
}


void Game::Run() {
    //ChangeScene(Scene::Title);
    ChangeScene(Scene::Platformer);
    //ChangeScene(Scene::FaceYassy);
    //ChangeScene(Scene::LevelSelect);

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
                platformer->Quit();
            }
            if (scene == Scene::FaceYassy) {
                faceyassy->Output();
            }
        }
        if (event.F12) {
            screenshot->SaveScreenShot();
        }
        accumulator -= settings::dt;

    }
}

void Game::HandleEvent() {
    input->GetKey();
    input->GetCursor();
    input->GetEvent();
}

void Game::Update() {
    //refresh
    OBJRECT screenRect = { (double)settings::baseW / 2, (double)settings::baseH / 2, (double)settings::baseW, (double)settings::baseH, 1 };
    textures->DrawRect({ 255,255,255,255 }, screenRect, 0);

    if (scene == Scene::Title) {
        title->Update();
    }

    if (scene == Scene::Platformer) {
        platformer->Update();
    }

    /*
    if (scene == Scene::Platformer) {
        platformer::flames++;

        CAMERA cam = camera->GetCam();
        OBJRECT screenRect = { (double)settings::baseW / 2, (double)settings::baseH / 2, (double)settings::baseW, (double)settings::baseH, 1 };
        textures->DrawRect({ 255,255,255,255 }, screenRect, 0);
        background->Draw();

        //UPDATE
        for (auto& obj : objects) {
            obj->Update();
        }
        
        textures->Update();

        for (auto& p : pendingObjects) {
            objects.push_back(std::move(p));
        }
        pendingObjects.clear();


        textures->Update();
        camera->Update();
        level->DrawMap();
        assy->Update();
        assy->Draw();
        //assy->DrawPlayer();
        
        for (auto& obj : objects) {
            obj->Draw();
        }
        
        

        objects.erase(
            std::remove_if(objects.begin(), objects.end(),
                [](const std::unique_ptr<GameObject>& o)
                {return o->IsDead(); }),
            objects.end()
        );

        level->Editor();

        

    }
    */

    if (scene == Scene::FaceYassy) {
        faceyassy->Update();
    }

    if (scene == Scene::LevelSelect) {
        levelselect->Update();
    }

    overlay->Update();
    textures->Update();

    //DEBUG INFO
    bool showCursorPoint = 0;
    bool showCross = 0;
    if (showCursorPoint) {
        int x, y;
        x = input->mouse.x;
        y = input->mouse.y;

        SDL_Color white = { 255,255,255,255 };
        SDL_Color black = { 0,0,0,255 };
        std::string text = std::to_string(x) + "," + std::to_string(y);
        textures->DrawTexts(text, white, black, { 0,50,1,1 }, 0, Anchor::Left);

        //cursor in window
        if (input->event.F1) {
            std::cout << text << std::endl;
        }
    }
    if (showCross) {
        int x, y;
        x = input->mouse.x;
        y = settings::baseH - input->mouse.y - 1;
        SDL_SetRenderDrawColor(settings::renderer, 0,0,0,255);
        SDL_RenderDrawLine(settings::renderer, x, y-2000, x, y+2000);
        SDL_RenderDrawLine(settings::renderer, x-2000, y, x+2000, y);

    }
}

void Game::InitSystem() {
    SetProcessDPIAware();
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    
    SDL_Surface* surface = IMG_Load("Assets/textures/cursor.png");
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
    settings::winW = (int)(settings::baseW * scale);
    settings::winH = (int)(settings::baseH * scale);
    settings::window = SDL_CreateWindow("YASSY STORY: awakening", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, settings::winW, settings::winH, SDL_WINDOW_FULLSCREEN_DESKTOP);
    //settings::window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, 0);
    settings::renderer = SDL_CreateRenderer(settings::window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    SDL_RenderSetLogicalSize(settings::renderer, settings::baseW, settings::baseH);

    SDL_RendererInfo info;
    SDL_GetRendererInfo(settings::renderer, &info);

    SDL_DisplayMode disp;
    SDL_GetDesktopDisplayMode(0, &disp);
    std::cout << "[DEBUG]リフレッシュレート：" << disp.refresh_rate << std::endl;
}


void Game::MakeInstance() {
    camera = std::make_unique<Camera>();
    textures = std::make_unique<Textures>();
    sounds = std::make_unique<Sounds>();
    input = std::make_unique<Input>();
    screenshot = std::make_unique<ScreenShot>();
    overlay = std::make_unique<OverLay>();
    
    
    OverLay::texturesP = textures.get();
    FaceYassy::inputP = input.get();
    FaceYassy::texturesP = textures.get();
    FaceYassy::gameP = this;
    Button::texturesP = textures.get();
    Button::inputP = input.get();
    Button::soundsP = sounds.get();
    Title::texturesP = textures.get();
    Title::overlayP = overlay.get();
    Title::gameP = this;
    Title::inputP = input.get();
    Options::soundsP = sounds.get();
    Options::texturesP = textures.get();

    //NEW
    Camera::texturesP = textures.get();
    Camera::inputP = input.get();
    Textures::cameraP = camera.get();
    Platformer::texturesP = textures.get();
    Platformer::cameraP = camera.get();
    Platformer::inputP = input.get();
    Platformer::soundsP = sounds.get();
    Level::texturesP = textures.get();
    Level::inputP = input.get();
    Level::cameraP = camera.get();
    Level::gameP = this;
    Player::cameraP = camera.get();
    Player::overlayP = overlay.get();
    LevelSelect::texturesP = textures.get();
    LevelSelect::gameP = this;
    UIManager::inputP = input.get();
    GameObject::texturesP = textures.get();
    GameObject::soundsP = sounds.get();
    GameObject::inputP = input.get();
    GameObject::cameraP = camera.get();
    
}

void Game::ExitGame() {
    running = 0;
}

void Game::Quit() {
    SDL_DestroyWindow(settings::window);
    SDL_Quit();
}