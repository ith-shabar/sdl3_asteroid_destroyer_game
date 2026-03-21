#ifndef TEXTUI_H
#define TEXTUI_H

#include "ui.h"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class TextUi : public Ui {
    private:
        TTF_Font * font = nullptr;
        SDL_Texture *texture = nullptr;
        SDL_Color color = {255, 255, 255, 255};
        std::string formatted_text;

    public:
        TextUi();
        ~TextUi();

        void setFont(const char *path, int size);
        void setColor(Uint8 r ,Uint8 g ,Uint8 b ,Uint8 a);
        void setFormat(const char *fmt, ...);

        void update() override;
        void updateBound() override;
        void render(SDL_Renderer *renderer) override;


};

#endif // !TEXTUI_H

