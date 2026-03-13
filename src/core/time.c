#include <SDL3/SDL.h>
#include <stdint.h>
#include "time.h"

static uint64_t last_time = 0;
static float dt = 0.0f;

void updateTime() {
    uint64_t current_time = SDL_GetTicks();

    if (last_time == 0) {
        last_time = current_time;
        return;
    }

    dt = (current_time - last_time) / 1000.0f;

    //capping
    if (dt > 0.05f) dt = 0.05f;
    if (dt < 0.0f) dt = 0.0f;

    last_time = current_time;
}

float deltaTime() {
    return dt;
}

uint64_t getTime(){
    uint64_t time = SDL_GetTicks();
    return time;
}

void capFPS(uint64_t start_frame){
    uint64_t end_frame = SDL_GetTicks();
    float frame_time = (float)(end_frame - start_frame);
    // this delays the next cycle if the current cycle has ended within FRAME_TICKS
    if (frame_time < FRAME_TICKS) SDL_Delay((uint64_t)FRAME_TICKS - frame_time); 
}
