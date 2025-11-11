#pragma once
#include <SDL3/SDL.h>

namespace Clock {
    extern float deltaTime;
    extern Uint64 lastFrameTime;
    extern Uint64 performanceFrequency;

    void init();
    void Update();
}