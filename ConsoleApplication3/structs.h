#include <vector>

#pragma once

struct MOUSE {
    int x;
    int y;
    bool left;
    bool middle;
    bool right;
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
};

struct BLOCKROOM {
	int x;
	int y;
	std::vector<std::vector<uint8_t>> terrain;
};

enum class entityType {
    Null,
    Lift,
    Zako
};

struct EVENT {
    bool ESCAPE;
    bool F12;
    int MouseWheel;
    bool MouseLeft;
    bool MouseMiddle;
    bool MouseRight;
    bool MouseX1;
    bool MouseX2;
};