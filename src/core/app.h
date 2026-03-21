#ifndef APP_H
#define APP_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

typedef SDL_Texture texture;

class App {
    private:
        SDL_Window *window = nullptr;
        static SDL_Renderer *renderer;

    public:
        int init();
        int initTTF();

        int renderWindow(char *title, int width, int height, uint32_t flags);

        texture *createTextureFromSurface(const char* file_path);

        void renderClear();
        void display();

        static SDL_Renderer *getRenderer();

        void quitApp();
        static void quitAppAndPrintError();
};


#endif 
