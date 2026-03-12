#include "../core/time.h"
#include "../core/algorithm.h"
#include "player.h"
#include "variables.h"

#include <cmath>

void Player::update(){
   float vx = 0,vy = 0;

   multi_key_press = keyS + keyD + keyA + keyW;

   float current_player_speed = player_speed;
   if (multi_key_press >= 2) current_player_speed = player_speed / 1.414f;

   if (keyD) vx += current_player_speed;
   if (keyA) vx -= current_player_speed;
   if (keyW) vy -= current_player_speed;
   if (keyS) vy += current_player_speed;

   if (keySpace || keyMouseButtonLeft) fireBullet();
  
   setVelocity(vx,vy);
   Entity::update();

   calculateRotation();
   updateBound();

   //update bullet
   getBulletManager().update();
}

void Player::render(SDL_Renderer * renderer){
    Entity::render(renderer);
    getBulletManager().render(renderer); 
}

void Player::calculateRotation(){
    float mouse_x ,mouse_y;

    SDL_GetMouseState(&mouse_x, &mouse_y);

    float rotation = std::atan2((mouse_y - position.y), (mouse_x - position.x));
    rotation = rotation * (180/3.14) + 90;
    setRotation(rotation);
}

void Player::handleInput(SDL_Event &event){

    if (event.type == SDL_EVENT_KEY_DOWN){
        if (event.key.key == SDLK_D) keyD = true;
        if (event.key.key == SDLK_A) keyA = true;
        if (event.key.key == SDLK_W) keyW = true;                   
        if (event.key.key == SDLK_S) keyS = true;
        if (event.key.key == SDLK_SPACE) keySpace = true;
    }
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) { keyMouseButtonLeft = true; }

    if (event.type == SDL_EVENT_KEY_UP) {
        if (event.key.key == SDLK_D) keyD = false;
        if (event.key.key == SDLK_A) keyA = false;
        if (event.key.key == SDLK_W) keyW = false;
        if (event.key.key == SDLK_S) keyS = false;
        if (event.key.key == SDLK_SPACE) keySpace = false;
    }
    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == SDL_BUTTON_LEFT) { keyMouseButtonLeft = false; }
}

void Player::fireBullet(){
    static uint64_t last_fire_time, current_time;
    const int delay = bullet_delay;

    // Random offset for bullet spread
    int offsetAngle = getRandomNUmber(0, bullet_spread);

    current_time = getTime();

    if ((current_time - last_fire_time) >= delay) {
        Entity* bullet = new Entity();
        bullet->setPosition(position.x, position.y);

        bullet->setTexture(bullet_texture, 0, 0, 3, 3);
        bullet->setScale(2);

        float angle_radian = (rotation - 90 + offsetAngle) * (3.14/180);
        float velocity_x = std::cos(angle_radian) * bullet_speed;
        float velocity_y = std::sin(angle_radian) * bullet_speed;

        bullet->setVelocity(velocity_x,velocity_y);

        bullets.add(bullet);
        last_fire_time = current_time;
    }
}

void Player::setBulletTex(SDL_Texture * texture){ bullet_texture = texture; }


void Player::setHealth(int health){ player_health = health; }
int Player::getHealth(){ return player_health; }


BulletManager& Player::getBulletManager(){ return bullets; }

