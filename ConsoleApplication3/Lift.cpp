#include <iostream>
#include <cmath>
#include "Lift.h"
#include "namespace.h"

Lift::Lift(double spawnX, double spawnY, int initialDirection) {
    h = 90;
    collision = { 0,1,0,0 };
    texName = "5";
    x = spawnX;
    y = spawnY;
    posX = spawnX;
    posY = spawnY;
    direction = initialDirection;
    amplitude = 80;
    speed = 80;

    if ( !(initialDirection == 1 || initialDirection == -1)) {
        std::cout << "リフト生成エラー: initialDirectionの値が不正です";
    }

}

void Lift::Update() {
    vX = speed * direction;
    MoveX();

    if (std::abs(x - posX) >= amplitude) {
        x = posX + (amplitude - 1) * direction;
        direction = direction * -1;
    }
    
}