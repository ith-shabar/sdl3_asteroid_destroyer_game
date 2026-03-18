#include "asteroid.h"
#include "variables.h"

#include "../core/algorithm.h"
#include "../core/time.h"

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <ostream>

void Asteroid::update(){

    static uint64_t current_time, last_time;

    current_time = getTime();
    uint64_t delta_time = current_time - last_time;
    if (delta_time >= asteroid_delay) {
        spwan();
        if (asteroid_delay > asteroid_min_delay) asteroid_delay -= 1;
        if (asteroid_speed < asteroid_max_speed) asteroid_speed += 1;
        
        last_time = current_time;
    }

    asteroids.cleanUp();

    Entity::update();
    asteroids.update();
}

void Asteroid::spwan(){
    int position_x, position_y;
    int asteroid_pos_offset = 100;
    float velocity_offset = getRandomNUmber(-100, 100);
    float rotation_offset = getRandomNUmber(0, 30);
    int texture_index = getRandomNUmber(0, 2);

    screen_side edge = screen_side(getRandomNUmber(0, 3));
    // set the intial position of the asteroid to be on the top by setting the x and y position
    if (edge == top){ 
        position_x = getRandomNUmber(0, SCREEN_WIDTH);
        position_y = -asteroid_pos_offset;
    } else if (edge == bottom){
        position_x = getRandomNUmber(0, SCREEN_WIDTH);
        position_y = SCREEN_HEIGHT + asteroid_pos_offset;
    } else if (edge == left){ 
        position_x = -asteroid_pos_offset;
        position_y = getRandomNUmber(0, SCREEN_HEIGHT);
    } else if (edge == right){
        position_x = SCREEN_WIDTH + asteroid_pos_offset;
        position_y = getRandomNUmber(0, SCREEN_HEIGHT);
    }

    Asteroid* asteroid = new Asteroid();
    asteroid->setTextureList(texture_list);
    asteroid->setTexture(getTextureList()[texture_index], 0, 0, 30, 30);
    asteroid->setPosition(position_x, position_y);
    asteroid->setScale(getRandomNUmber(1, 3));
    asteroid->updateBound();

    // For each edge, calculate angle toward a random point in the screen
    float targetX = getRandomNUmber(0, SCREEN_WIDTH);
    float targetY = getRandomNUmber(0, SCREEN_HEIGHT);
    float direction_angle_radians = std::atan2(targetY - position_y, targetX - position_x);
    float velocity_x = std::cos(direction_angle_radians) * (asteroid_speed + velocity_offset);
    float velocity_y = std::sin(direction_angle_radians) * (asteroid_speed - velocity_offset);

    asteroid->setRotationSpeed(getRandomNUmber(-3, 3));

    asteroid->setVelocity(velocity_x,velocity_y);

    asteroids.add(asteroid);
}

// Collision 
void Asteroid::onCollision(Entity *other){
    if (!other->getActive()) return; // return if other is not active

    if (other->getTypeID() == 3) { // for bullet vs asteroid
        other->setActive(false);
        if (this->getScale() > 2) {
            this->setScale(this->getScale()-1);
        }else {
            this->setActive(false);
        }
        score += 10;
    } else if (other->getTypeID() == 2) {// for asteroid vs asteroid
        int size1 = this->getScale();
        int size2 = other->getScale();

        float dx = this->getPositionX() - other->getPositionX();
        float dy = this->getPositionY() - other->getPositionY();

        float distance = std::sqrt(dx*dx + dy*dy);

        float nx = dx / distance;
        float ny = dy / distance;

        //relative veloccity
        float dvx = this->getVelocityX() - other->getVelocityX();
        float dvy = this->getVelocityY() - other->getVelocityY();

        //velocity along normal
        float dot_product = dvx * nx + dvy * ny;

        //impulse calculate
        float impulse = (2 * dot_product) / (size1 + size2);

        //bounce 
        this->velocity.x -= impulse * nx * size2;
        this->velocity.y -= impulse * ny * size2;
        other->velocity.x += impulse * nx * size1;
        other->velocity.y += impulse * ny * size1;

     }
}

void Asteroid::render(SDL_Renderer *renderer){
    Entity::render(renderer);
    getAsteroidManager().render(renderer);
}

void Asteroid::setAsteroidTex(SDL_Texture *texture){ asteroid_texture = texture;}

void Asteroid::setHealth(int hp){ health = hp;}
int Asteroid::getHealth(){ return health;}

int Asteroid::getTypeID() const { return type_id;}

AsteroidManager& Asteroid::getAsteroidManager(){ return asteroids; }

