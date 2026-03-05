#include "app.h"

int App::init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("%s: %s\n","Error occured when initialising SDL_INIT_VIDEO", SDL_GetError());
        return 1;
    }
    return 0;
}

int App::renderWindow(char *title, int width, int height, uint32_t flags){

    if(!SDL_CreateWindowAndRenderer(title, width, height, flags, &window, &renderer)){
        SDL_Log("%s: %s\n","Error occured when creating a window or a renderer", SDL_GetError());
        return 1;
    }
    return 0;
}

SDL_Texture* App::createTextureFromSurface(const char* file_path){
    SDL_Texture *texture = NULL;
    SDL_Surface *surface;

    surface = IMG_Load(file_path);
    if (surface == NULL) {
        SDL_Log("%s: %s\n","Error occured when loading surface", SDL_GetError());
    }
    
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        SDL_Log("%s: %s\n","Error occured when creating a texture", SDL_GetError());
    } 
    SDL_DestroySurface(surface);

    return texture;
}

void App::renderClear(){
     SDL_RenderClear(renderer);
}

void App::display(){
    SDL_RenderPresent(renderer);
}


SDL_Renderer *App::getRenderer(){
    return renderer;
}
