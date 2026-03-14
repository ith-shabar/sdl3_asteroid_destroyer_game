#ifndef ASTEROID_H
#define ASTEROID_H

#include "../core/entity.h"
#include "asteroidmanager.h"

class Asteroid : public Entity {
    private:
        bool active;
        int health;
        AsteroidManager asteroids;
        SDL_Texture *asteroid_texture = nullptr;

    public:
        void spwan();
        void update() override;
        void render(SDL_Renderer *renderer) override;

        void setAsteroidTex(SDL_Texture *texture);

        void setHealth(int health);
        int getHealth();

        AsteroidManager& getAsteroidManager();
};

#endif // !PLAYER_H
