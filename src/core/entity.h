#ifndef ENTITY_H
#define ENTITY_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

#include <vector>

class Entity {
    public:
        SDL_FPoint position = {0.0f, 0.0f};
        SDL_FPoint velocity = {0.0f, 0.0f};
        float rotation = 0.0f;
        float rotation_speed = 0.0f;
        float scale = 1.0f;

        SDL_Texture *texture = nullptr;
        std::vector<SDL_Texture*> texture_list;

        SDL_FRect bound = {0.0f, 0.0f, 0.0f, 0.0f};
        SDL_FRect src_rect = {0.0f, 0.0f, 0.0f, 0.0f};
        SDL_FRect dst_rect = {0.0f, 0.0f, 0.0f, 0.0f};

        bool active = true;

        Entity(SDL_FPoint pos = {0.0f, 0.0f});
        ~Entity();

        virtual void update();
        virtual void render(SDL_Renderer *renderer);
        virtual void onCollision(Entity *other);

        void updateBound();

        //Setters
        void setTexture(SDL_Texture *tex, int x, int y, int width , int height);
        void setTextureList(std::vector<SDL_Texture*> tex_list);

        void setPosition(SDL_FPoint pos);
        void setPosition(float x , float y);
        void setPositionX(float x);
        void setPositionY(float y);

        void setVelocity(SDL_FPoint vel);
        void setVelocity(float x, float y);
        void setVelocityX(float x);
        void setVelocityY(float y);

        void setRotation(float rot);
        void setRotationSpeed(float rot_speed);
        void setScale(float scl);

        void setActive(bool act);

        //Getters
        SDL_FPoint getPosition();
        float getPositionX();
        float getPositionY();
        SDL_FPoint getVelocity();
        float getVelocityX();
        float getVelocityY();

        float getRotation();
        float getRotationSpeed();
        float getScale();

        SDL_Texture *getTexture();
        std::vector<SDL_Texture*> getTextureList();

        SDL_FRect getBound();
        SDL_FRect getSrcRect();
        SDL_FRect getDstRect();
        bool getActive();

        int getHeight();
        int getWidth();

};

#endif
