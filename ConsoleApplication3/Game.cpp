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
#include "FaceYassy.h"
#include "Button.h"
#include "CheckPoint.h"

Game::Game() 
{
    running = true;
    scene = Scene::Platformer;
    sceneReserve = Scene::Title;
    timer.SetTime(1.0);
}

/*リセットしないインスタンス↓
* camera
* textures
* sounds
* input
* screenshot
* overlay
*/

void Game::SceneChanging() {
    timer.SetTime(10.0);
    Mix_HaltMusic();

    background.reset();
    faceyassy.reset();
    title.reset();
    platformer.reset();
    levelselect.reset();

    scene = sceneReserve;
    if (sceneReserve == Scene::Title) {
        title = std::make_unique<Title>();

        title->Init();
    }
    if (sceneReserve == Scene::Platformer) {
        platformer = std::make_unique<Platformer>();
        GameObject::platformerP = platformer.get();

        camera->Init();

        platformer->Init();
    }

    if (sceneReserve == Scene::FaceYassy) {
        faceyassy = std::make_unique<FaceYassy>();
        faceyassy->RegisterButtons();
    }

    if (sceneReserve == Scene::SlotSelect) {
        levelselect = std::make_unique<LevelSelect>();
        levelselect->phase = PhaseLevelSelect::SelectSlot;
        levelselect->GetPercent();
        sounds->PlayMusic("the_snippet");
    }

    if (sceneReserve == Scene::LevelSelect) {
        levelselect = std::make_unique<LevelSelect>();
        levelselect->phase = PhaseLevelSelect::SelectLevel;
        sounds->PlayMusic("the_snippet");
    }

    overlay->FadeIn(1.0, { 0,0,0,255 });
}

void Game::ChangeScene(Scene s) {
    sceneReserve = s;
    timer.Reset();
    overlay->FadeOut(1.0, { 0,0,0,255 });
}


void Game::Run() {
    ChangeScene(Scene::Title);
    //ChangeScene(Scene::Platformer);
    //ChangeScene(Scene::FaceYassy);
    //ChangeScene(Scene::LevelSelect);
    timer.SetTime(1.0);

    save->LoadOptions();

    double accumulator = 0.0;
    double lastTime = SDL_GetTicks() / 1000.0;

    while (running) {
        double currentTime = SDL_GetTicks() / 1000.0;
        double frameTime = currentTime - lastTime;
        lastTime = currentTime;
        if (frameTime > 0.1) frameTime = 0.1;
        settings::timeScale = frameTime * settings::multiplier;
        
        input->Update();
        if (timer.GetTime() < 1.0) {
            input->TurnInput(false);
        }
        else {
            input->TurnInput(true);
        }
        Update();
        
        //textures->DrawTexts(std::to_string(Mix_GetMusicPosition(NULL)), { 0,0,0,255 }, { 0,50,1,1 }, 0, {});

        const Uint8* keystate = input->keystate;
        const EVENT event = input->event;

        if (event.Q) {
            running = 0;
            if (scene == Scene::Platformer) {
                platformer->Quit();
            }
            if (scene == Scene::FaceYassy) {
                faceyassy->Output();
            }
            save->WriteOptions();
        }
        
        if (event.F12) {
            screenshot->SaveScreenShot();
        }
        accumulator -= settings::dt;

    }
}


void Game::Update() {
    std::cout << platformer::level;
    //refresh
    SDL_Rect screenRect = { 0, 0, settings::baseW, settings::baseH};
    SDL_SetRenderTarget(settings::renderer, NULL);
    SDL_SetRenderDrawColor(settings::renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(settings::renderer, &screenRect);
    SDL_SetRenderTarget(settings::renderer, textures->GetCanvas());

    double time = timer.GetTime();
    if (1.0 <= time && time < 2.0) {
        SceneChanging();
        return;
    }

    if (scene == Scene::Title) {
        title->Update();
    }

    if (scene == Scene::Platformer) {
        platformer->Update();
    }

    if (scene == Scene::FaceYassy) {
        faceyassy->Update();
    }

    if (scene == Scene::SlotSelect || scene == Scene::LevelSelect) {
        levelselect->Update();
    }

    overlay->Update();
    textures->Update();

    

    //DEBUG INFO
    bool showCursorPoint = 1;
    bool showCross = 1;
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
    std::cout << disp.refresh_rate << std::endl;
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
    Title::soundsP = sounds.get();
    Options::soundsP = sounds.get();
    Options::texturesP = textures.get();
    Options::inputP = input.get();

    //NEW
    Camera::texturesP = textures.get();
    Camera::inputP = input.get();
    Textures::cameraP = camera.get();
    Platformer::texturesP = textures.get();
    Platformer::cameraP = camera.get();
    Platformer::inputP = input.get();
    Platformer::soundsP = sounds.get();
    Platformer::saveP = save.get();
    Platformer::gameP = this;
    Level::texturesP = textures.get();
    Level::soundsP = sounds.get();
    Level::inputP = input.get();
    Level::cameraP = camera.get();
    Level::gameP = this;
    Player::cameraP = camera.get();
    Player::overlayP = overlay.get();
    LevelSelect::texturesP = textures.get();
    LevelSelect::gameP = this;
    LevelSelect::inputP = input.get();
    LevelSelect::saveP = save.get();
    UIManager::inputP = input.get();
    GameObject::texturesP = textures.get();
    GameObject::soundsP = sounds.get();
    GameObject::inputP = input.get();
    GameObject::cameraP = camera.get();
    Save::inputP = input.get();
    Save::soundsP = sounds.get();
    CheckPoint::saveP = save.get();
    Pause::texturesP = textures.get();
    Pause::gameP = this;
    Pause::saveP = save.get();
    Pause::inputP = input.get();
}

void Game::ExitGame() {
    running = 0;
}

void Game::Quit() {
    SDL_DestroyWindow(settings::window);
    SDL_Quit();
}