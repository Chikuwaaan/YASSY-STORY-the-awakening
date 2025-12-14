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
    CAMERA getCam();
    void setCam(CAMERA cam);
    void Update();
};

