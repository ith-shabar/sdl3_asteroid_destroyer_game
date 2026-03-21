#include "textui.h"
#include "app.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include <cstdarg>
#include <cstdio>

TextUi::TextUi() :font(nullptr), texture(nullptr) {}

TextUi::~TextUi() {
    if (texture) SDL_DestroyTexture(texture);
    if (font) TTF_CloseFont(font);
}


void TextUi::setFont(const char *path, int size){
    font = TTF_OpenFont(path, size);
    if (!font) App::quitAppAndPrintError();
}
void TextUi::setColor(Uint8 r ,Uint8 g ,Uint8 b ,Uint8 a){
    color = {r, g, b, a};
}
void TextUi::setFormat(const char *fmt, ...){

    char buffer[128];
    va_list args;
    va_start(args , fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    formatted_text = buffer;
}

void TextUi::update() {
    Ui::update();  
}

void TextUi::updateBound() {
  if (!texture) return;

    float w, h;
    SDL_GetTextureSize(texture, &w, &h);

    float final_w = w * scale;
    float final_h = h * scale;

    bound = {
        position.x - final_w * 0.5f,
        position.y - final_h * 0.5f,
        final_w,
        final_h
    };
}

void TextUi::render(SDL_Renderer *renderer) {
    if (!font || !active) return;

    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }


    SDL_Surface *surface = TTF_RenderText_Blended(font, formatted_text.c_str(),formatted_text.length(), color);
    if (!surface) App::quitAppAndPrintError();

    texture = SDL_CreateTextureFromSurface(App::getRenderer(), surface);
    SDL_DestroySurface(surface);

    if (!texture) App::quitAppAndPrintError();
    
    float w,h;
    SDL_GetTextureSize(texture, &w, &h);

    dst_rect = {
        position.x - (w * scale) * 0.5f,
        position.y - (h * scale) * 0.5f,
        static_cast<float>(w * scale),
        static_cast<float>(h * scale)
    };

    SDL_RenderTexture(App::getRenderer(), texture, nullptr, &dst_rect);
}

