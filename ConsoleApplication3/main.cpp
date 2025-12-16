#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include <string>
#include <map>
#include <windows.h>
#include <cmath>

#include "namespace.h"
#include "structs.h"
#include "Textures.h"
#include "Camera.h"
#include "Level.h"
#include "GameObject.h"
#include "Player.h"

int main(int argc, char* argv[]) {
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

	TTF_Font* font100 = TTF_OpenFont("C:/Windows/Fonts/meiryo.ttc", 50);
	if (!font100) {
		std::cout << "フォントが読み込めませんでした。";
		return 1;
	}
	
    //Open Window
	SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
	float scaleX = (float)dm.w / settings::baseW;
	float scaleY = (float)dm.h / settings::baseH;
	float scale = (scaleX < scaleY) ? scaleX : scaleY;
	int winW = (int)(settings::baseW * scale);
	int winH = (int)(settings::baseH * scale);
	settings::window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winW, winH, SDL_WINDOW_FULLSCREEN_DESKTOP);
	settings::renderer = SDL_CreateRenderer(settings::window, -1, SDL_RENDERER_SOFTWARE);
    SDL_RenderSetLogicalSize(settings::renderer, settings::baseW, settings::baseH);
    

	std::vector<std::unique_ptr<GameObject>> objects;
	std::vector<std::unique_ptr<GameObject>> pending;
	Camera camera;
	Textures textures;
	Level level;
	Player Assy2("assy2");
	GameObject::texturesP = &textures;
	GameObject::cameraP = &camera;
	//GameObject::pendingP = &pending;
	Level::texturesP = &textures;
	Player::levelP = &level;	
	Player::cameraP = &camera;
	Camera::texturesP = &textures;
    Textures::cameraP = &camera;
	

	double accumulator = 0.0;
	double lastTime = SDL_GetTicks() / 1000.0;

	SDL_Color color = { 0, 0, 0 };
	SDL_Event event;
	bool running = true;


	while (running) {    
        CAMERA cam = camera.GetCam();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			if (event.type == SDL_MOUSEWHEEL) {
                cam.zoom = cam.zoom + event.wheel.y * 0.1;
                camera.SetCam(cam);
				//camera.SetZoom(camera.getCam().zoom + event.wheel.y * 0.1);
			}
		}

		double currentTime = SDL_GetTicks() / 1000.0;
		double frameTime = currentTime - lastTime;
		lastTime = currentTime;
		accumulator += frameTime;
		
		while (accumulator >= settings::dt) {
			SDL_RenderSetLogicalSize(settings::renderer, settings::baseW, settings::baseH);
			const Uint8* keystate = SDL_GetKeyboardState(NULL);
			if (keystate[SDL_SCANCODE_RIGHT]) {
				//camera.SetOffsetX(camera.GetOffsetX() + 4 * timeScale * 60);
			}
			if (keystate[SDL_SCANCODE_LEFT]) {
				//camera.SetOffsetX(camera.GetOffsetX() - 4 * timeScale * 60);
			}
			if (keystate[SDL_SCANCODE_SPACE]) {
				textures.LoadTextures();
				//Mix_Music* music = Mix_LoadMUS("Assets/audio/YASSY_ZONE.wav");
				//Mix_PlayMusic(music, -1);
			}
			if (keystate[SDL_SCANCODE_W]) {
				Assy2.Jump();
			}
			if (keystate[SDL_SCANCODE_A]) {
				Assy2.SetAX(-3840.0);
                Assy2.FlipX(true);
			}
			if (keystate[SDL_SCANCODE_D]) {
				Assy2.SetAX(3840.0);
                Assy2.FlipX(false);
			}
            if (keystate[SDL_SCANCODE_ESCAPE]) {
                running = false;
            }

			for (auto& obj : objects) {
				obj->Update();
			}
			Assy2.Update();
			for (auto& p : pending) {
				objects.push_back(std::move(p));
			}
			pending.clear();

			//std::cout << std::endl;
			SDL_RenderPresent(settings::renderer);
			accumulator -= settings::dt;
		}

		//SDL_RenderSetLogicalSize(renderer, (int)(baseW / camera.getCam().zoom), (int)(baseH / camera.getCam().zoom));
		//SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        //SDL_Rect viewPort = { 0, 0, 1440, 1080 };
        //SDL_RenderSetViewport(settings::renderer, &viewPort);
        SDL_SetRenderDrawColor(settings::renderer, 117, 226, 255, 255);
        SDL_Rect rect = { 0, 0, settings::baseW, settings::baseH };
        SDL_RenderFillRect(settings::renderer, &rect);

        /*
		camera.targetX = Assy2.GetX() + camera.GetOffsetX();
		camera.targetY = Assy2.GetY();
		Assy2.MoveCameraRoom();
		camera.SetX(camera.targetX + (camera.getCam().x - camera.targetX) / (1.02));
		camera.SetY(camera.targetY + (camera.getCam().y - camera.targetY) / (1.02));
        */
		
		level.DrawMap();
		for (auto& obj : objects) {
			obj->Draw();
		}
		//Assy2.Draw();
		Assy2.DrawPlayer();


		
        /*
		color = { 255,255,255 };
		DrawText(font100, std::to_string(Assy2.GetX()), color, 0, 200);
		DrawText(font100, std::to_string(Assy2.GetY()), color, 0, 300);
		DrawText(font100, std::to_string(camera.getCam().x), color, 200, 400);
		DrawText(font100, std::to_string(camera.getCam().y), color, 200, 500);
		DrawText(font100, std::to_string(camera.targetX), color, 400, 600);
		DrawText(font100, std::to_string(camera.targetY), color, 400, 700);
        */

        //SDL_Rect rect = { 100,100,100,100 };
        //SDL_RenderCopy(settings::renderer, IMG_LoadTexture(settings::renderer, "Assets/textures/assy.png"), NULL, &rect);
        textures.Update();
        camera.Update();
        color = { 255,255,255,255 };
        textures.DrawTextA("unchi", color, 0, 0);
		SDL_RenderPresent(settings::renderer);
	}

	SDL_DestroyWindow(settings::window);
	SDL_Quit();
	return 0;
}