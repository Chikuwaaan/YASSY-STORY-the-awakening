#include "Eye.h"
#include "Textures.h"

Eye::Eye(double R) {
    r = R;
    x = 758;
    y = 581;
    w = r*2;
    h = r*2;

    irisX = r/2;
    irisY = 0;
    irisVX = 0;
    irisVY = 0;

    theta = 0;
}

void Eye::Update(double AX, double AY) {
    irisVX -= AX * settings::timeScale;
    irisVY -= AY * 2 * settings::timeScale;

    irisVY += r * -20 * settings::timeScale;

    irisX += irisVX * settings::timeScale;
    irisY += irisVY * settings::timeScale;
    
    theta = std::atan2(irisY, irisX);
    angle = std::atan2(irisVY, irisVX);

    double distance;
    distance = irisX * irisX + irisY * irisY;
    if (distance > (r/2)*(r/2)) {
        irisVX = cos(theta) * r * -5 * random.frandom(0.9,1.1);
        irisVY = sin(theta) * irisVY * 0.8 * random.frandom(0.9, 1.1);
        irisVY += sin(theta) * abs(AX) * -0.01;

        irisX = cos(theta) * r / 2;
        irisY = sin(theta) * r / 2;
    }
}

void Eye::Draw() {
    texturesP->DrawImage("circle_black", {x,y,w*1.1,h*1.1}, 1, {});
    texturesP->DrawImage("circle_mask", {x,y,w,h}, 1, {});
    texturesP->DrawImage("circle_black", { x+irisX,y+irisY,w/2,h/2 }, 1, {});
}