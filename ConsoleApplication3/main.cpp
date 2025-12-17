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

#include "Game.h"

int main(int argc, char* argv[]) {
    Game game;
    game.InitSystem();

	std::vector<std::unique_ptr<GameObject>> objects;
	std::vector<std::unique_ptr<GameObject>> pending;
	Camera camera;
	Textures textures;
	Level level;
	Player Assy2;
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

    int flames = 0;
    bool countFlame = true;
    double fpsAccum = 0.0;
    int realFps = 0;

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
        fpsAccum += frameTime;
		
		while (accumulator >= settings::dt) {
            if (countFlame) {
                flames++;
                countFlame = false;
            }

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
        countFlame = true;

		//SDL_RenderSetLogicalSize(renderer, (int)(baseW / camera.getCam().zoom), (int)(baseH / camera.getCam().zoom));
		//SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        //SDL_Rect viewPort = { 0, 0, 1440, 1080 };
        //SDL_RenderSetViewport(settings::renderer, &viewPort);
        SDL_SetRenderDrawColor(settings::renderer, 117, 226, 255, 255);
        SDL_Rect rect = { 0, 0, settings::baseW, settings::baseH };
        SDL_RenderFillRect(settings::renderer, &rect);

        if (fpsAccum > 1.0) {
            realFps = (int)round(flames / fpsAccum);
            fpsAccum -= 1.0;
            flames = 0;
        }
        color = { 255,255,255,255 };
        textures.DrawTextA(std::to_string(realFps), color, 0, 0, 1, 1);
		
		level.DrawMap();
		for (auto& obj : objects) {
			obj->Draw();
		}
		//Assy2.Draw();
		Assy2.DrawPlayer();
        textures.Update();
        camera.Update();
		SDL_RenderPresent(settings::renderer);
	}

	SDL_DestroyWindow(settings::window);
	SDL_Quit();
	return 0;
}