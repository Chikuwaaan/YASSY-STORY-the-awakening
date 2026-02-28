#include <vector>
#include <map>
#include <string>

#pragma once

struct POSITION {
    double x;
    double y;
};

struct ROTATE {
    bool rotate;
    double angle;
    double centerX;
    double centerY;
    bool flipX;
    bool flipY;
};


struct CAMERA {
	double x;
	double y;
    double offsetX;
    double offsetY;
    double targetX;
    double targetY;
	double zoom;
};

struct OBJRECT {
	double x = 0.0;
	double y = 0.0;
	double w = 100.0;
	double h = 100.0;
	int block = 0;
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
    bool force;
};

struct BLOCKROOM {
	int x;
	int y;
	std::vector<std::vector<uint8_t>> terrain;
};

