#include "FaceYassy.h"
#include <iostream>

#include "namespace.h"
#include "Input.h"
#include "structs.h"
#include "Textures.h"
#include "Button.h"
#include "UIManager.h"
#include "Game.h"

Input* FaceYassy::inputP = nullptr;
Textures* FaceYassy::texturesP = nullptr;
Game* FaceYassy::gameP = nullptr;

FaceYassy::FaceYassy() :
    test(64,64,128,128)
{
    layer = 0;
    trajectories.push_back({});
    trajectoriesModded = {};
    grabx = 0;
    graby = 0;
    mousedx = 0;
    mousedy = 0;

    trajectories.push_back({
        {557,723},
{643,913},
{760,738},
{1097,738},
{1187,904},
{1277,736},
{1348,624},
{1365,482},
{1324,327},
{1247,285},
{1113,242},
{897,228},
{768,232},
{620,244},
{523,280},
{477,396},
{478,515},
{501,641},
        });
    trajectories.push_back({
        {682,606},
{848,611},
{711,516},
{760,670},
{817,524},
        });
    trajectories.push_back({
        {982,614},
{1118,615},
{996,522},
{1044,677},
{1111,520},
        });
    trajectories.push_back({
        {765,482},
{1045,479},
{1006,419},
{897,398},
{798,426},
        });
    trajectories.push_back({
        {527,496},
{571,437},
        });
    trajectories.push_back({
        {613,500},
{657,443},
        });
    trajectories.push_back({
        {1173,497},
{1207,440},
        });
    trajectories.push_back({
        {1262,500},
{1291,447},
        });

    

}

void FaceYassy::Delete() {
    layer = 0;
    trajectories.clear();
    trajectories.push_back({});
}

void FaceYassy::Update() {
    SDL_Renderer* r = settings::renderer;
    OBJRECT bg = { settings::baseW/2,settings::baseH/2,settings::baseW,settings::baseH };
    texturesP->DrawImage("rokuyon", bg, 0, {});

    SDL_SetRenderDrawColor(r, 255,255,255, 255);

    int mouseX = (int)inputP->mouse.x;
    int mouseY = (int)inputP->mouse.y;

    //std::cout << trajectories.size();

    if (inputP->event.E) {
        layer++;
        if (layer >= trajectories.size()) {
            trajectories.push_back({});
        }
    }
    if (inputP->event.Q) layer--;
    if (inputP->event.DEL) {
        test.action();
    }

    if (!ui.IsCursorOnUI()) {
        if (inputP->event.MouseLeft) {
            trajectories[layer].push_back({ mouseX,mouseY });
        }
        if (inputP->event.MouseRight) {
            grabx = (int)inputP->mouse.x;
            graby = (int)inputP->mouse.y;
        }
        if (inputP->mouse.right) {
            mousedx = inputP->mouse.x - grabx;
            mousedy = inputP->mouse.y - graby;
        }
        else {
            mousedx = 0;
            mousedy = 0;
        }
    }
    
    std::cout << mousedx << "," << mousedy << ",";
    if (mousedx) std::cout << tan((mousedy*0.1) / mousedx);
    std::cout << std::endl;
    
    /*
    double angle = 0;
    if (mousedx != 0) {
        angle = 1 / tan(mousedy / mousedx);
    }
    else {
        angle = 0;
    }
    std::cout << angle << std::endl;
    */
    

    //MOD
    trajectoriesModded.clear();
    for (int i = 0; i < trajectories.size(); i++) {
        trajectoriesModded.push_back({});
        for (int j = 0; j < trajectories[i].size(); j++) {
            int effect = (abs(trajectories[i][j].x - grabx) * (abs(trajectories[i][j].x - grabx)));
            effect = effect + (abs(trajectories[i][j].y - graby) * (abs(trajectories[i][j].y - graby)));
            effect = effect + 80000;
            int x = (int)round(trajectories[i][j].x + 40000.0 / effect * mousedx);
            int y = (int)round(trajectories[i][j].y + 40000.0 / effect * mousedy);
            trajectoriesModded[i].push_back({x, y});
        }
    }

    //DRAW
    for (int i = 0; i < trajectoriesModded.size(); i++) {
        for (int j = 0; j < trajectoriesModded[i].size(); j++) {
            SDL_Point current, next;
            current = { trajectoriesModded[i][j].x, settings::baseH - trajectoriesModded[i][j].y };
            int k = j + 1;
            if (k >= trajectoriesModded[i].size()) k = 0;
            next = { trajectoriesModded[i][k].x, settings::baseH - trajectoriesModded[i][k].y };
            if (k != 0 || 1) {
                SDL_RenderDrawLine(r, current.x, current.y, next.x, next.y);
            }
        }
    }
}

void FaceYassy::Output() {
    for (int i = 0; i < trajectories.size(); i++) {
        for (int j = 0; j < trajectories[i].size(); j++) {
            std::cout << "{" << trajectories[i][j].x << "," << trajectories[i][j].y << "}," << std::endl;
        }
        std::cout << std::endl;
    }

}

void FaceYassy::RegisterButtons() {
    //ui.AddButton(&test);
    test.action = [this]() {
        this->gameP->ChangeScene(Scene::Platformer);
        };
}