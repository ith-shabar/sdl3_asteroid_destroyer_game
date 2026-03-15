#ifndef PLAYER_H
#define PLAYER_H

#include "../core/entity.h"
#include "bulletmanager.h"

#include <SDL3/SDL.h>

class Player : public Entity {
    private:
        bool active = true;
        bool moving = false;
        BulletManager bullets;
        SDL_Texture *bullet_texture = nullptr;

        static constexpr int type_id = 1;
    public:
        void update() override;
        void render(SDL_Renderer *renderer) override;
        void calculateRotation();
        void handleInput(SDL_Event &event);

        void setBulletTex(SDL_Texture *texture);
        void fireBullet();

        void setHealth(int health);
        int getHealth();

        void onCollision(Entity *other) override;

        int getTypeID() const override;
        BulletManager& getBulletManager();
};

#endif // !PLAYER_H
