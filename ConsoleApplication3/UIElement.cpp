#include "UIElement.h"
#include "Textures.h"

Textures* UIElement::texturesP = nullptr;

UIElement::UIElement(int UI, int Element) {
    x = 0;
    y = 0;
    w = 0;
    h = 0;
    UInum = UI;
    elementNum = Element;
    SetUp();
}

void UIElement::Update() {
    texturesP->DrawRect({ 0,0,0,255 }, { x,y,w,h }, 0);
}

void UIElement::SetUp() {
    if (UInum == 0) {
        if (elementNum == 0) {
            w = 200;
            h = 100;
        }
    }
}