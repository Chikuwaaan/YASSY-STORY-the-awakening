#pragma once

#include "structs.h"
#include <vector>

class Camera
{
private:
    CAMERA camera;
    std::vector<CAMERAROOM> room;
public:
    Camera();
    CAMERA getCam();
    void setCam(CAMERA cam);
};

