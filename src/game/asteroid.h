#ifndef ASTEROID_H
#define ASTEROID_H

#include "../core/entity.h"
#include "asteroidmanager.h"
#include "variables.h"

class Asteroid : public Entity {
    private:
        bool active;
        int health;
        AsteroidManager asteroids;
        SDL_Texture *asteroid_texture = nullptr;

        static constexpr id_types id_type = asteroid;

    public:
        void spwan();
        void update() override;
        void render(SDL_Renderer *renderer) override;

        void setAsteroidTex(SDL_Texture *texture);

        void setHealth(int health);
        int getHealth();

        void onCollision(Entity *other) override;

        int getTypeID() const override;
        AsteroidManager& getAsteroidManager();
};

#endif // !PLAYER_H
