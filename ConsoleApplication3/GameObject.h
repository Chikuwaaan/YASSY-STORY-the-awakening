#pragma once

#include <string>
#include <vector>

class Textures;
class Camera;

class GameObject
{
protected:
    std::string texName;
    double x, y, w, h;
    double vX, vY;
public:
    static Textures* texturesP;
    static Camera* cameraP;

    virtual void Update() = 0;
    GameObject();
    void MoveX();
    void MoveY();
    void Draw();
};

