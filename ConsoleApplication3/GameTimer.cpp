#include "GameTimer.h"
#include "namespace.h"

GameTimer::GameTimer() {
    timer = 0;
}

void GameTimer::Update() {
    timer += settings::timeScale;
}

void GameTimer::Reset() {
    timer = 0;
}

double GameTimer::GetTime() {
    return timer;
}

void GameTimer::SetTime(double sec) {
    timer = sec;
}