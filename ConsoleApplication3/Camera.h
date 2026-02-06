#pragma once

#include "structs.h"
#include <vector>
class Textures;
class Input;

class Camera
{
private:
    CAMERA camera;
    std::vector<CAMERAROOM> room;
    bool drawCameraRoom;
public:
    static Textures* texturesP;
    static Input* inputP;
    Camera();

    void LoadCameraRoom(int n);

    CAMERA GetCam();
    void Init();
    void SetCam(CAMERA cam);
    void SetTargetX(double x);
    void SetTargetY(double y);
    void Update();
    std::vector<CAMERAROOM>* GetRoom();
};

