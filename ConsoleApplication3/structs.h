#include <vector>

#pragma once

struct CAMERA {
	double x;
	double y;
	double zoom;
};

struct OBJRECT {
	double x;
	double y;
	double w;
	double h;
	bool touch = false;
};

struct CAMERAROOM {
	double x1;
	double x2;
	double y1;
	double y2;
	double x3;
	double x4;
	double y3;
	double y4;
};

struct BLOCKROOM {
	int x;
	int y;
	std::vector<std::vector<int>> terrain;
};