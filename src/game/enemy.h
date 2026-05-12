#ifndef ENEMY_H
#define ENEMY_H

#include "../core/entity.h"
#include "bulletmanager.h"
#include "variables.h"

#include <SDL3/SDL.h>

class Enemy : public Entity {
    private:
        BulletManager bullets;
        SDL_Texture *bullet_texture = nullptr;

        static constexpr id_types id_type = enemy;

    public:
        void update() override;
        void render(SDL_Renderer *renderer) override;
        void calculateRotation();

        void setEnemyTex(SDL_Texture *texture);
        void fireBullet();

        void setHealth(int health);
        int getHealth();

        void onCollision(Entity *other) override;

        int getTypeID() const override;
        BulletManager& getBulletManager();
};

#endif // !ENEMY_H
