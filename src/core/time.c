#include <SDL3/SDL.h>
#include <stdint.h>
#include "time.h"

static uint64_t last_time = 0;

float deltaTime(){
    uint64_t current_time = SDL_GetTicks();
    float dt = (current_time - last_time) / 1000.0f;
    last_time = current_time;

    //clamping the deltatime to 50ms
    if (dt > 0.05f) dt = 0.05f;
    if (dt < 0.0f) dt = 0.0f;

    return dt;
}

void updateTime(){
    uint64_t current_time = SDL_GetTicks();
    if (last_time == 0) last_time = current_time;
}

uint64_t getTime(){
    uint64_t time = SDL_GetTicks();
    return time;
}

void capFPS(uint64_t start_frame){
    uint64_t end_frame = SDL_GetTicks();
    uint64_t frame_time = end_frame - start_frame;
    // this delays the next cycle if the current cycle has ended within FRAME_TICKS
    if (frame_time < FRAME_TICKS) SDL_Delay(FRAME_TICKS - frame_time); 
}
