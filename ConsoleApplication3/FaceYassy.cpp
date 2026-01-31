#include "FaceYassy.h"
#include <iostream>

#include "namespace.h"
#include "Input.h"
#include "structs.h"
#include "Textures.h"

Input* FaceYassy::inputP = nullptr;
Textures* FaceYassy::texturesP = nullptr;

FaceYassy::FaceYassy() {
    layer = 0;
    trajectories.push_back({});
    trajectoriesModded = {};
    grabx = 0;
    graby = 0;
    mousedx = 0;
    mousedy = 0;
}

void FaceYassy::Update() {
    SDL_Renderer* r = settings::renderer;
    SDL_Rect refresh = { 0,0,settings::baseW,settings::baseH };
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderFillRect(r, &refresh);

    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);

    int mouseX = (int)inputP->mouse.x;
    int mouseY = (int)inputP->mouse.y;
    SDL_Color color = { 0,0,0,255 };
    texturesP->DrawTexts(std::to_string(mouseX) + " " + std::to_string(mouseY), color, {0,0,1,1}, 0, {});
    texturesP->DrawTexts("layer" + std::to_string(layer), color, { 1500,0,1,1 }, 0, {});

    //std::cout << trajectories.size();

    if (inputP->event.E) {
        layer++;
        if (layer >= trajectories.size()) {
            trajectories.push_back({});
        }
    }
    if (inputP->event.Q) layer--;
    if (inputP->event.MouseLeft) {
        trajectories[layer].push_back({mouseX,mouseY});
    }
    if (inputP->event.DEL) {
        layer = 0;
        trajectories.clear();
        trajectories.push_back({});
    }


    if (inputP->event.MouseRight) {
        grabx = (int)inputP->mouse.x;
        graby = (int)inputP->mouse.y;
    }
    if (inputP->mouse.right) {
        mousedx = inputP->mouse.x - grabx;
        mousedy = inputP->mouse.y - graby;
        texturesP->DrawTexts(std::to_string(mousedx) + " " + std::to_string(mousedy), color, { 0,50,1,1 }, 0, {});
    }
    else {
        mousedx = 0;
        mousedy = 0;
    }


    trajectoriesModded.clear();
    for (int i = 0; i < trajectories.size(); i++) {
        trajectoriesModded.push_back({});
        for (int j = 0; j < trajectories[i].size(); j++) {
            /*
            std::uniform_int_distribution<int> dist(-5, 5);
            int dx = dist(gen);
            int dy = dist(gen);
            int x = trajectories[i][j].x + dx;
            int y = trajectories[i][j].y + dy
            */
            int x = trajectories[i][j].x + 100.0 / (abs(trajectories[i][j].x - grabx) + 200) * mousedx;
            int y = trajectories[i][j].y + 100.0 / (abs(trajectories[i][j].y - graby) + 200) * mousedy;
            trajectoriesModded[i].push_back({x, y});
        }
    }

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