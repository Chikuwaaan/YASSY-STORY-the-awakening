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

/*
void DrawImage(SDL_Texture* texture, OBJRECT rect, CAMERA camera,  bool horizontalFlip, bool verticalFlip, double angle, double axisX, double axisY) {
	SDL_Rect dst;
	double pivotX = baseW / 2.0;
	double pivotY = baseH / 2.0;
	//dst.x = (int)(rect.x - rect.w * 0.5 - (camera.x - pivotX + baseW * (0.5 - 0.5 / camera.zoom)));
	//dst.y = (int)(baseH - (rect.y + rect.h * 0.5) + (camera.y - pivotY - baseH * (0.5 - 0.5 / camera.zoom)));
	dst.x = (int)((rect.x - rect.w * 0.5 - (camera.x - pivotX + baseW * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
	dst.y = (int)(baseH - ((rect.y + rect.h * 0.5) - (camera.y - pivotY + baseH * (0.5 - 0.5 / camera.zoom))) * camera.zoom);
	dst.w = (int)(rect.w * camera.zoom);
	dst.h = (int)(rect.h * camera.zoom);
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (horizontalFlip && verticalFlip) {
		flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	}
	else if (horizontalFlip) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	else if (verticalFlip) {
		flip = SDL_FLIP_VERTICAL;
	}
	SDL_Point center;
	center.x = (int)(axisX * camera.zoom);
	center.y = (int)(axisY * camera.zoom);

	SDL_RenderCopyEx(settings::renderer, texture, NULL, &dst, angle , &center, flip);
}

void DrawTextU8(TTF_Font* font, const char8_t* textIn, SDL_Color color, double x, double y) {
	const char* text = reinterpret_cast<const char*>(textIn);
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	OBJRECT dst = { x, y, (double)surface->w, (double)surface->h };
	CAMERA cam = { 0, 0, 1 };
	DrawImage(texture, dst, cam, 0, 0, 0, 0, 0);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void DrawText(TTF_Font* font, std::string textIn, SDL_Color color, int x, int y) {
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, textIn.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect dst = { x, y, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, NULL, &dst);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}
*/

/*
class Camera {
private:
	CAMERA camera;
	double offsetX = 0.0;
	std::vector<CAMERAROOM> room;
public:
	double targetX = 0.0;
	double targetY = 0.0;

	static Player* playerP;
	Camera() {
		camera.x = 960.0;
		camera.y = 540.0;
		camera.zoom = 1.0;

		room.push_back({ 0,1920,0,1080,960,960,540,540 });
		room.push_back({1920,1920*2,0,1440,960*3-120,960*3+120,540,660});
	}

	void SetX(double x) {
		camera.x = x;
	}
	void SetY(double y) {
		camera.y = y;
	}
	void SetTargetX(double x) {
		targetX = x;
	}
	void SetTargetY(double y) {
		targetY = y;
	}
	void SetZoom(double zoom) {
		camera.zoom = zoom;
	}
	double GetOffsetX() {
		return offsetX;
	}
	void SetOffsetX(double amount) {
		double range = 200.0;
		offsetX = amount;
		if (offsetX > range) {
			offsetX = range;
		}
		else if (offsetX < -1 * range) {
			offsetX = -1 * range;
		}
	}

	std::vector<CAMERAROOM>* GetRoom() {
		return &room;
	}
	
	

	CAMERA getCam() {
		return camera;
	}
};
Player* Camera::playerP = nullptr;
*/

/*
class Textures {
private:
	std::map<std::string, SDL_Texture*> map;
	int x = 0, y = 0;
public:
	Textures() {
		LoadTextures();
	}

	void LoadTextures() {
		for (auto [_, value] : map) {
			SDL_DestroyTexture(value);
		}

		map["missing"] = IMG_LoadTexture(renderer, "Assets/textures/missing.png");;
		map["1"] = IMG_LoadTexture(renderer, "Assets/textures/BAN.png");
		map["2"] = IMG_LoadTexture(renderer, "Assets/textures/dokufee.png");
		map["assy"] = IMG_LoadTexture(renderer, "Assets/textures/assy.png");
		map["assy2"] = IMG_LoadTexture(renderer, "Assets/textures/assy2.png");
		map["assyChara"] = IMG_LoadTexture(renderer, "Assets/textures/assyChara.png");
		map["legL"] = IMG_LoadTexture(renderer, "Assets/textures/legL.png");
		map["legR"] = IMG_LoadTexture(renderer, "Assets/textures/legR.png");
		map["body"] = IMG_LoadTexture(renderer, "Assets/textures/body.png");
		map["head"] = IMG_LoadTexture(renderer, "Assets/textures/head.png");
		map["armL"] = IMG_LoadTexture(renderer, "Assets/textures/armL.png");
		map["armR"] = IMG_LoadTexture(renderer, "Assets/textures/armR.png");
		map["unko"] = IMG_LoadTexture(renderer, "Assets/textures/unko.png");
	}

	SDL_Texture* getTexture(std::string name) {
		if (map.count(name) == 0) {
			return map["missing"];
		}
		else {
			return map[name];
		}
	}
};
*/

/*
class LLevel {
private:
	std::vector<BLOCKROOM> rooms;
	double blockSize = 120;

public:
	static Textures* texturesP;
	static Camera* cameraP;

	Level() {
		
		rooms.push_back({ 0,0,{
			{0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,1,0,1,0,1,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0},
			{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,0,1,0,0,0,1,0,0,0,1,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0},
			{0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,1,1,0,0,0,1,0,0},
			{0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
} });
		rooms.push_back({ -1,0,{
			{0,0,2},
			{0,0,0},
			{2,0,0}
} });
		rooms.push_back({ 32,9,{
			{0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,2,2,2},
			{0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,2,0,0},
			{0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,2,0,0,0},
			{0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0},
			{2,2,2,0,0,0,0,0,0},
} });
		rooms.push_back({ 49,5,{
			{2}
}});
		
	};

	void DrawMap() {
		const int room = (int)rooms.size();

		for (int h = 0; h < room ; h++) {
			int row = (int)rooms[h].terrain.size();
			int column = (int)rooms[h].terrain[0].size();
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < column; j++) {
					std::string texName = std::to_string(rooms[h].terrain[i][j]);
					if (texName != "0") {
						OBJRECT rect;
						rect.x = blockSize * (j + 0.5) + blockSize * rooms[h].x;
						rect.y = blockSize * (row - (i + 0.5)) + blockSize * rooms[h].y;
						rect.w = blockSize;
						rect.h = blockSize;
                        texturesP->DrawImage(texName, rect, cameraP->getCam());
					}
				}
			}
		}

	};
   


	OBJRECT IsTouching(OBJRECT obj1) {
		bool a = false;
		const int room = (int)rooms.size();
		const int width = (int)(obj1.w / blockSize) + 1;
		const int height = (int)(obj1.h / blockSize) + 1;

		for (int h = 0; h < room; h++) {
			int row = (int)rooms[h].terrain.size();
			int column = (int)rooms[h].terrain[0].size();
			int levelX = rooms[h].x;
			int levelY = rooms[h].y;
			int playerLevelX = (int)(obj1.x / blockSize) - levelX;
			int playerLevelY = row - (int)(obj1.y / blockSize) - 1 + levelY;

			int i = playerLevelY - height;
			int j;
			int k = playerLevelY + height;
			int l = playerLevelX + width;
			if (i < 0) i = 0;
			if (k > (row - 1)) k = row - 1;
			for (; i <= k; i++) {
				j = playerLevelX - width;
				if (j < 0) j = 0;
				if (l > (column - 1)) l = column - 1;

				for (; j <= l; j++) {
					if (rooms[h].terrain[i][j] != 0) {
						OBJRECT obj2 = { blockSize * (j + levelX + 0.5) , blockSize * (row - (i - levelY + 0.5)) , blockSize, blockSize };
						//DrawImage(texturesP->getTexture("unko"), obj2, cameraP->getCam(), 0, 0, 0, 0, 0);
						//std::cout << obj2.x << "," << obj2.y << std::endl;
						a = utilities::HitDetection(obj1, obj2);
						if (a) {
							return { blockSize * (j + levelX + 0.5), blockSize * (row - (i - levelY + 0.5)), blockSize, blockSize, true };
						}
					}
				}
			}
		}

		
		return { 0, 0, 0, 0, false };
	}

	double getBlockSize() {
		return blockSize;
	}
};
Textures* Level::texturesP = nullptr;
Camera* Level::cameraP = nullptr;
*/

/*
class GameObject {
protected:
	std::string texName;
	double x = 0.0, y = 500.0;
	double w = 200.0, h = 200.0;
	double angle = 0.0;
	bool flipX = false, flipY = false;
public:
	static Textures* texturesP;
	static Camera* cameraP;
	static std::vector<std::unique_ptr<GameObject>>* pendingP;

	virtual void Update() {};

	GameObject() {
		//w = width;
		//h = height;
	}

	void MoveX(double distance) {
		x += distance * settings::timeScale;
	}

	void MoveY(double distance) {
		y += distance * settings::timeScale;
	}

	double GetX() {
		return x;
	}
	double GetY() {
		return y;
	}
	double GetW() {
		return w;
	}
	double GetH() {
		return h;
	}

	void Draw() {
		OBJRECT rect = { x,y,w,h };
        texturesP->DrawImage(texName, rect);
	}
};
Textures* GameObject::texturesP = nullptr;
Camera* GameObject::cameraP = nullptr;
std::vector<std::unique_ptr<GameObject>>* GameObject::pendingP = nullptr;
*/

/*
class PPlayer : public GameObject {
private:
	bool onGround = false;
	double maxSpeed = 480.0;
	double minSpeed = 8.0;
	double deceleration = 1920.0;
	double moveBody = 0;
public:
	static Level* levelP;
	static Camera* cameraP;


	Player(std::string tex){
		texName = "missing";
		x = 180.0;
		y = 1000.0;
		w = 60.0;
		h = 100.0;
	};

	double getvX() {
		return vX;
	}

	void SetAX(double acceleration) {
		vX += acceleration * settings::timeScale;
		if (vX > maxSpeed) {
			vX = maxSpeed;
		}
		else if (vX < -1*maxSpeed){
			vX = -1 * maxSpeed;
		}

        
		if (acceleration > 0.0) {
			flipX = false;
		}
		else if (acceleration < 0.0) {
			flipX = true;
		}
        
	}

	OBJRECT isTouchingMap(double x, double y, double w, double h) {
		OBJRECT obj = { x, y, w, h };
		return levelP->IsTouching(obj);
	}


	void Update() override {


		vY -= 2000 * settings::timeScale;
		
		
		OBJRECT touchingMap;
		//Y
		MoveY();
		onGround = false;
		touchingMap = isTouchingMap(x, y, w, h);
		while (touchingMap.touch && vY < 0.0) {
			onGround = true;
			vY = 0.0;
			y = touchingMap.y + 0.5*h + levelP->GetBlockSize()*0.5;
			touchingMap = isTouchingMap(x, y, w, h);
		}
		while (touchingMap.touch && vY > 0.0) {
			vY = 0.0;
			y = touchingMap.y - 0.5 * h - levelP->GetBlockSize() * 0.5;
			touchingMap = isTouchingMap(x, y, w, h);
		}
		
		//X
		MoveX();
		touchingMap = isTouchingMap(x, y, w, h);
		while (touchingMap.touch) {
			if (vX > 0.0) {
				vX = 0.0;
				x = touchingMap.x - 0.5 * w - levelP->GetBlockSize() * 0.5;
				touchingMap = isTouchingMap(x, y, w, h);
			}
			else if (vX < 0.0) {
				vX = 0.0;
				x = touchingMap.x + 0.5 * w + levelP->GetBlockSize() * 0.5;
				touchingMap = isTouchingMap(x, y, w, h);
			}
			else {
				break;
			}
		}

		if (vX >= minSpeed) {
			vX -= deceleration * settings::timeScale;
		}
		else if (vX < minSpeed && vX > minSpeed*-1) {
			vX = 0.0;
		}
		else if (vX <= minSpeed*-1) {
			vX += deceleration * settings::timeScale;
		}
		else {
			vX = 0.0;
		}

		if (y < -1000.0) {
			x = 180.0;
			y = 180.0;
			w = 60.0;
			h = 100.0;
			//Mix_Music* music = Mix_LoadMUS("Assets/audio/sanctuary.wav");
			//Mix_PlayMusic(music, -1);
		}

		if (!onGround) {
			moveBody += 12 * settings::timeScale;
		}

		if (vX != 0.0) {
			moveBody += 12 * settings::timeScale;
		}
		else if (onGround) {
			moveBody = 0;
		}

	}

	void Jump() {
		if (onGround) {
			vY = 1250.0;
		}
	}

    
	void MoveCameraRoom() {
		std::vector<CAMERAROOM>* room = cameraP->GetRoom();
		for (int i = 0; i < room->size(); i++) {
			if (x > (*room)[i].x1 && x < (*room)[i].x2 && y >(*room)[i].y1 && y < (*room)[i].y2) {
				if ((*room)[i].x3 > cameraP->targetX) {
					cameraP->SetTargetX((*room)[i].x3);
				} else
				if ((*room)[i].x4 < cameraP->targetX) {
					cameraP->SetTargetX((*room)[i].x4);
				}
				if ((*room)[i].y3 > cameraP->targetY) {
					cameraP->SetTargetY((*room)[i].y3);
				} else
				if ((*room)[i].y4 < cameraP->targetY) {
					cameraP->SetTargetY((*room)[i].y4);
				}
			}
		}
		
	}
    


    
	void DrawPart(std::string texName, double angle, double axisX, double axisY) {
		SDL_Texture* texture = texturesP->getTexture(texName);
		double rectX = 140 * (w/60);
		double rectY = 140 * (h/100);
		OBJRECT rect = { x + 20 + flipX*-40, y + 6, rectX, rectY};
		DrawImage(texture, rect, cameraP->getCam(), flipX, 0, angle, flipX ? (rectX - axisX * rectX / 140) : axisX * rectX/140, axisY * rectY / 140);
	}

	void DrawPlayer() {
		DrawPart("legL", sin(moveBody) * 16, 30, 60);
		DrawPart("legR", sin(moveBody)*-16, 34, 60);
		DrawPart("body", sin(moveBody), 0, 0);
		DrawPart("head", sin(moveBody) * 4, 80, 20);
		DrawPart("armL", sin(moveBody) * -16, 90, 60);
		DrawPart("armR", sin(moveBody) * 16, 70, 70);
	}
    
};
Level* Player::levelP = nullptr;
Camera* Player::cameraP = nullptr;

*/





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
		SDL_SetRenderDrawColor(settings::renderer, 100, 50, 50, 255);
		SDL_RenderClear(settings::renderer);


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
		Assy2.Draw();
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