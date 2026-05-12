#ifndef AUDIO_H
#define AUDIO_H

#define MAX_SFX 32
#define MAX_MUSIC 16

#include <SDL3_mixer/SDL_mixer.h>

class Audio {
    private:
        static Audio *instance;
        
        Mix_Chunk *sfx[MAX_SFX] = {nullptr};
        Mix_Music *music[MAX_MUSIC] = {nullptr};

        int sfx_volume = 64;
        int music_volume = 64;

        bool initialised = false;

    public:
        Audio() = default;

        int init();
        bool isInitialised() const { return initialised;}

        static Audio *getInstance();

        //sfx 
        int loadSfx(int id, const char* path);
        void playSfx(int id, int loops = 0);

        void setVolume(int volume);
        int getVolume() const {return sfx_volume;}

        //music 
        //...

        void cleanup();

        ~Audio() { cleanup(); }

};

#endif
