#include "bulletmanager.h"
#include "variables.h"
#include "../core/time.h"
#include "../core/algorithm.h"

#include <cmath>

void BulletManager::update(){
    for (auto * bullet  :entities) {
        if (!bullet->getActive()) continue;
        bullet->update();
    }
    cleanUp();
}

void BulletManager::render(SDL_Renderer *renderer){
    for (auto *bullet : entities) {
        if (bullet->getActive()) {
            bullet->render(renderer);
        }
    }
}

void BulletManager::spawn(SDL_FPoint position, float rotation){
    static uint64_t last_fire_time, current_time;
    const int delay = bullet_delay;

    int offsetAngle = getRandomNUmber(0, bullet_spread);

    current_time = getTime();

    if ((current_time - last_fire_time) >= delay) {
        Bullet *bullet = new Bullet();
        bullet->setPosition(position.x, position.y);

        bullet->setTexture(bullet_texture, 0, 0, 3, 3);
        bullet->setScale(2);
        bullet->updateBound();

        float angle_radian = (rotation - 90 + offsetAngle) * (3.14f / 180.0f);
        float velocity_x = std::cos(angle_radian) * bullet_speed;
        float velocity_y = std::sin(angle_radian) * bullet_speed;

        bullet->setVelocity(velocity_x, velocity_y);

        add(bullet);
        last_fire_time = current_time;
    }
}

void BulletManager::setBulletTexture(SDL_Texture *texture) { bullet_texture = texture; }
