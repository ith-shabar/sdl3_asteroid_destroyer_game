#ifndef UI_H
#define UI_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

#include <vector>

class Ui {
    public:
        SDL_FPoint position = {0.0f, 0.0f};
        float rotation = 0.0f;
        float scale = 1.0f;

        SDL_Texture *texture = nullptr;

        SDL_FRect bound = {0.0f, 0.0f, 0.0f, 0.0f};
        SDL_FRect src_rect = {0.0f, 0.0f, 0.0f, 0.0f};
        SDL_FRect dst_rect = {0.0f, 0.0f, 0.0f, 0.0f};

        bool active = true;
        const int type_id = 0;

        Ui(SDL_FPoint pos = {0.0f, 0.0f});
        ~Ui();

        virtual void update();
        virtual void render(SDL_Renderer *renderer);
        virtual void checkHover();
        virtual void onHover(SDL_FRect *rect);

        virtual void checkClick();
        virtual void onClick(SDL_FRect *rect);

        virtual void updateBound();

        //Setters
        void setTexture(SDL_Texture *tex, int x, int y, int width , int height);

        void setPosition(SDL_FPoint pos);
        void setPosition(float x , float y);
        void setPositionX(float x);
        void setPositionY(float y);

        void setRotation(float rot);
        void setScale(float scl);

        void setActive(bool act);

        //Getters
        SDL_FPoint getPosition();
        float getPositionX();
        float getPositionY();

        float getRotation();
        float getScale();

        SDL_Texture *getTexture();

        SDL_FRect getBound();
        SDL_FRect getSrcRect();
        SDL_FRect getDstRect();
        bool getActive();

        virtual int getTypeID() const;

        int getHeight();
        int getWidth();

};

#endif
