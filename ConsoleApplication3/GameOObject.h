#pragma once

#include <string>
#include <vector>
#include <iostream>
class Textures;
class Camera;


class GameOObject
{
protected:
	std::string texName;
	double x, y, w, h;
	double angle;
	bool flipX, flipY;
public:
	static Textures* texturesP;
	static Camera* cameraP;
	static std::vector<std::unique_ptr<GameOObject>>* pendingP;

	GameOObject();
	double GetX();
	double GetY();
	double GetW();
	double getH();
};

Textures* GameOObject::texturesP = nullptr;
Camera* GameOObject::cameraP = nullptr;
std::vector<std::unique_ptr<GameOObject>>* GameOObject::pendingP = nullptr;