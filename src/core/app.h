#ifndef APP_H
#define APP_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>

class App {
    private:
        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;

    public:
        int init();

        int renderWindow(char *title, int width, int height, uint32_t flags);

        SDL_Texture *createTextureFromSurface(const char* file_path);

        void renderClear();
        void display();

        SDL_Renderer *getRenderer();
};


#endif 
