#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "../core/entitymanager.h"
#include "bullet.h"

class BulletManager : public EntityManager<Bullet> {
    private:
        SDL_Texture *bullet_texture = nullptr;
    public:
        void update() override;
        void render(SDL_Renderer *renderer) override;
        void spawn(SDL_FPoint position, float rotation);

        void setBulletTexture(SDL_Texture *texture);

};

#endif
