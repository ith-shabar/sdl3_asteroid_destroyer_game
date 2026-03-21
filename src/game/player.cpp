#include "player.h"
#include "variables.h"

#include <cmath>
#include <iostream>

void Player::update(){
   float vx = 0,vy = 0;

   multi_key_press = keyS + keyD + keyA + keyW;

   float current_player_speed = player_speed;
   if (multi_key_press >= 2) current_player_speed = player_speed / 1.414f;

   if (keyD) vx += current_player_speed;
   if (keyA) vx -= current_player_speed;
   if (keyW) vy -= current_player_speed;
   if (keyS) vy += current_player_speed;

    if (keyD || keyS || keyW || keyA ) { moving = true;}
    else { moving = false; }

   if (bound.x + bound.w > SCREEN_WIDTH) vx -= player_speed;
   if (bound.y + bound.h > SCREEN_HEIGHT) vy -= player_speed;
   if (bound.x < 0) vx += player_speed;
   if (bound.y < 0) vy += player_speed;

   if (keySpace || keyMouseButtonLeft) fireBullet();

   if (moving) setTexture(getTextureList()[1], 0, 0, 30, 30);
   else setTexture(getTextureList()[0], 0, 0, 30, 30);
  
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
    bullets.spawn(position, rotation);
}

void Player::onCollision(Entity *other){
    if (!other->getActive()) return;

    if (other->getTypeID() == 2) {
        other->setActive(false);
        player_health -= 20;
        if (player_health <= 0) {
            this->setActive(false);
            mode = result;
            score_obtained = score;
        }
    }
}

void Player::setBulletTex(SDL_Texture * texture){ 
    bullets.setBulletTexture(texture); 
}


void Player::setHealth(int health){ player_health = health; }
int Player::getHealth(){ return player_health; }

int Player::getTypeID() const { return type_id;}

BulletManager& Player::getBulletManager(){ return bullets; }

