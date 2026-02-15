#include "Timer.h"
#include <iostream>

Timer::Timer() {
    last = 0;
    now = 0;
    delta = 0;
    timer = 0;
}

void Timer::Update() {
    now = SDL_GetTicks();
    delta = now - last;
    last = now;
    timer += delta / 1000.0;
}

void Timer::Reset() {
    std::cout << "‚è‚¹‚Á‚Æ";
    timer = 0;
}

double Timer::GetTime() {
    now = SDL_GetTicks();
    delta = now - last;
    last = now;
    timer += delta / 1000.0;
    std::cout << timer << std::endl;
    return timer;
}