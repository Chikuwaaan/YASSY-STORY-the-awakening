#pragma once

#include "structs.h"
#include <vector>
class Textures;

class Camera
{
private:
    CAMERA camera;
    std::vector<CAMERAROOM> room;
public:
    static Textures* texturesP;
    Camera();
    CAMERA GetCam();
    void SetCam(CAMERA cam);
    void SetTargetX(double x);
    void SetTargetY(double y);
    void Update();
    std::vector<CAMERAROOM>* GetRoom();
};

