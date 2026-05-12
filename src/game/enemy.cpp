#include "enemy.h"
#include "variables.h"

#include <cmath>


void Enemy::update(){
   float vx = 0,vy = 0;

   multi_key_press = keyS + keyD + keyA + keyW;

   float current_player_speed = player_speed;
   if (multi_key_press >= 2) current_player_speed = player_speed / 1.414f;

   if (keyD) vx += current_player_speed;
   if (keyA) vx -= current_player_speed;
   if (keyW) vy -= current_player_speed;
   if (keyS) vy += current_player_speed;


   if (bound.x + bound.w > SCREEN_WIDTH) vx -= player_speed;
   if (bound.y + bound.h > SCREEN_HEIGHT) vy -= player_speed;
   if (bound.x < 0) vx += player_speed;
   if (bound.y < 0) vy += player_speed;

   if (keySpace || keyMouseButtonLeft) fireBullet();

   else setTexture(getTextureList()[0], 0, 0, 30, 30);
  
   setVelocity(vx,vy);
   Entity::update();

   calculateRotation();
   updateBound();

   //update bullet
   getBulletManager().update();
}

void Enemy::render(SDL_Renderer * renderer){
    Entity::render(renderer);
    getBulletManager().render(renderer); 
}

void Enemy::calculateRotation(){
    float mouse_x ,mouse_y;

    SDL_GetMouseState(&mouse_x, &mouse_y);

    float rotation = std::atan2((mouse_y - position.y), (mouse_x - position.x));
    rotation = rotation * (180/3.14) + 90;
    setRotation(rotation);
}

void Enemy::fireBullet(){
    bullets.spawn(position, rotation);
}

void Enemy::onCollision(Entity *other){
    if (!other->getActive()) return;
}

void Enemy::setEnemyTex(SDL_Texture * texture){ 
    bullets.setBulletTexture(texture); 
}


void Enemy::setHealth(int health){ player_health = health; }
int Enemy::getHealth(){ return player_health; }

int Enemy::getTypeID() const { return id_type;}

BulletManager& Enemy::getBulletManager(){ return bullets; }

