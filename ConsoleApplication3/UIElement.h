#pragma once
#include "GameObject.h"

class Textures;

class UIElement :
    public GameObject
{
private:
    int UInum, elementNum;
public:
    static Textures* texturesP;
    UIElement(int UINum, int ElementNum);
    void Update();
    void SetUp();
};