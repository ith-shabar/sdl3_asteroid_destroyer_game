#include "audio.h"
#include "app.h"
#include <SDL3_mixer/SDL_mixer.h>

Audio *Audio::instance = nullptr;

Audio *Audio::getInstance() { 
    if (instance == nullptr) instance = new Audio();
    return instance;
}

int Audio::init() {
    if (initialised)  return 0;

    if (Mix_OpenAudio(0, nullptr) == 0) App::printError(); return -1;

    Mix_AllocateChannels(8);
    initialised = true;
    return 0;
}

int Audio::loadSfx(int id, const char *path) {
    if (id < 0 || id > MAX_SFX) return  -1;

    if (sfx[id] != nullptr) {
        Mix_FreeChunk(sfx[id]);
        sfx[id] = nullptr;
    }

    sfx[id] = Mix_LoadWAV(path);
    if (!sfx[id]) {
        App::printError();
        return -1;
    }
    return 0;
}

void Audio::playSfx(int id, int loops) {
    if (id < 0 || id > MAX_SFX || !sfx[id]) return ;

    int channel = Mix_PlayChannel(-1, sfx[id], loops);

    if (channel == -1) App::printError();
    
}

void Audio::setVolume(int volume) {
    sfx_volume = volume;
    Mix_Volume(-1, volume);
}

void Audio::cleanup() {
    for (int i = 0; i < MAX_SFX; i++) {
        if (sfx[i] != nullptr) {
            Mix_FreeChunk(sfx[i]);
            sfx[i] = nullptr;
        }
    }

    if (initialised) {
        Mix_CloseAudio();
        initialised = false;
    }
}
