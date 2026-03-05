#ifndef ENTITY_H
#define ENTITY_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

class Entity {
    protected:
        SDL_FPoint position = {0.0f, 0.0f};
        SDL_FPoint velocity = {0.0f, 0.0f};
        float rotation = 0.0f;
        float scale = 1.0f;

        SDL_Texture *texture = nullptr;
        SDL_FRect bound = {0.0f, 0.0f, 0.0f, 0.0f};
        SDL_FRect src_rect = {0.0f, 0.0f, 0.0f, 0.0f};
        SDL_FRect dst_rect = {0.0f, 0.0f, 0.0f, 0.0f};

        bool active = true;

    public:
        Entity(SDL_FPoint pos = {0.0f, 0.0f});
        ~Entity();

        virtual void update();
        virtual void render(SDL_Renderer *renderer);
        virtual void onCollision(Entity *other);

        void updateBound();

        //Setters
        void setTexture(SDL_Texture *tex, int x, int y, int width , int height);

        void setPosition(SDL_FPoint pos);
        void setPosition(float x , float y);

        void setVelocity(SDL_FPoint vel);
        void setVelocity(float x, float y);

        void setRotation(float rot);
        void setScale(float scl);

        void setActive(bool act);

        //Getters
        SDL_FPoint getPosition();
        SDL_FPoint getVelocity();

        float getRotation();
        float getScale();

        SDL_Texture *getTextutre();

        SDL_FRect getBound();
        SDL_FRect getSrcRect();
        SDL_FRect getDstRect();
        bool getActive();

        int getHeight();
        int getWidth();

};

#endif
