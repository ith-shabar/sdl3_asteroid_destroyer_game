#ifndef BULLET_H
#define BULLET_H

#include "../core/entity.h"
#include "variables.h"

class Bullet : public Entity {
    private:
        int health = 1;
        static constexpr id_types id_type = bullet;

    public:
        void update() override;
        void render(SDL_Renderer *renderer) override;

        void setHealth(int health);
        int getHealth();

        void onCollision(Entity *other) override;

        int getTypeID() const override;
};

#endif
