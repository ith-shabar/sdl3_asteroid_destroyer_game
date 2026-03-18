#include "bullet.h"
#include "variables.h"
#include "../core/algorithm.h"

#include <cmath>

void Bullet::update() {
    if (!active) return;
    Entity::update();

    if (position.x < 0 || position.x > SCREEN_WIDTH ||
        position.y < 0 || position.y > SCREEN_HEIGHT) {
        active = false;
    }
}

void Bullet::render(SDL_Renderer *renderer) {
    if (!active) return;
    Entity::render(renderer);
}

void Bullet::setHealth(int hp) { health = hp; }
int Bullet::getHealth() { return health; }

void Bullet::onCollision(Entity *other) {
}

int Bullet::getTypeID() const { return type_id; }
