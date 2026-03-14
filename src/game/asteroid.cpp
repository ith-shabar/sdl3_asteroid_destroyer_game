#include "asteroid.h"
#include "variables.h"

#include "../core/algorithm.h"
#include "../core/time.h"
#include "../core/entitymanager.h"

#include <cmath>
#include <cstdint>

void Asteroid::update(){
    Entity::update();

    static uint64_t current_time, last_time;

    current_time = getTime();
    if (current_time - last_time >= asteroid_delay) {
        spwan();
        last_time = current_time;
    }

    getAsteroidManager().update();
}

void Asteroid::spwan(){
    int position_x, position_y;
    int asteroid_pos_offset = 100;
    float direction_angle_degrees;
    float velocity_offset = getRandomNUmber(1, 2);
    float rotation_offset = getRandomNUmber(0, 30);

    // Random offset for incoming asteroid
    // ....

    screen_side edge = screen_side(getRandomNUmber(0, 3));
    // set the intial position of the asteroid to be on the top by setting the x and y position
    if (edge == top){ 
        position_x = getRandomNUmber(0, SCREEN_WIDTH);
        position_y = 0 - asteroid_pos_offset;
        direction_angle_degrees = getRandomNUmber(180, 360);
    } else if (edge == bottom){
        position_x = getRandomNUmber(0, SCREEN_WIDTH);
        position_y = SCREEN_HEIGHT + asteroid_pos_offset;
        direction_angle_degrees = getRandomNUmber(180,360);
    } else if (edge == left){ 
        position_x = 0 - asteroid_pos_offset;
        position_y = getRandomNUmber(0, SCREEN_HEIGHT);
        direction_angle_degrees = getRandomNUmber(90,270);
    } else if (edge == right){
        position_x = SCREEN_WIDTH + asteroid_pos_offset;
        position_y = getRandomNUmber(0, SCREEN_HEIGHT);
        direction_angle_degrees = getRandomNUmber(90,270);
    }

    Entity* asteroid = new Entity();
    asteroid->setTexture(asteroid_texture, 0, 0, 30, 30);
    asteroid->setPosition(position_x, position_y);
    asteroid->setScale(2);

    float direction_angle_radion = (direction_angle_degrees - rotation_offset) * (180/3.14);
    float velocity_x = std::cos(direction_angle_radion) * asteroid_speed * velocity_offset;
    float velocity_y = std::sin(direction_angle_radion) * asteroid_speed * velocity_offset;

    asteroid->setRotationSpeed(getRandomNUmber(-3, 3));

    asteroid->setVelocity(velocity_x,velocity_y);

    asteroids.add(asteroid);
}

void Asteroid::render(SDL_Renderer *renderer){
    Entity::render(renderer);
    getAsteroidManager().render(renderer);
}

void Asteroid::setAsteroidTex(SDL_Texture *texture){ asteroid_texture = texture;}

void Asteroid::setHealth(int hp){ health = hp;}
int Asteroid::getHealth(){ return health;}

AsteroidManager& Asteroid::getAsteroidManager(){ return asteroids; }

