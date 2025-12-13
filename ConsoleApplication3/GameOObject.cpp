#include "GameOObject.h"
#include "namespace.h"

GameOObject::GameOObject() {
	texName = "missing";
	x = 0.0;
	y = 0.0;
	w = 200.0;
	h = 200.0;
	angle = 0.0;
	flipX = false;
	flipY = false;
}

double GameOObject::GetX() {
	return x;
}

double GameOObject::GetY() {
	return y;
}

double GameOObject::GetW() {
	return w;
}

double GameOObject::getH() {
	return h;
}