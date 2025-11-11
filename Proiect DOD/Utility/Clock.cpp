#include "Clock.h"

namespace Clock {
    float deltaTime = 0.0f;
    Uint64 lastFrameTime = 0;
    Uint64 performanceFrequency = 0;
}

void Clock::init() {
    performanceFrequency = SDL_GetPerformanceFrequency();
    lastFrameTime = SDL_GetPerformanceCounter();
    deltaTime = 0.0f;
}

void Clock::Update() {
    Uint64 currentTime = SDL_GetPerformanceCounter();
    deltaTime = (float)(currentTime - lastFrameTime) / (float)performanceFrequency;
    lastFrameTime = currentTime;
}