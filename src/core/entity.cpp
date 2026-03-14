#include "entity.h"
#include "time.h"
#include <algorithm>

Entity::Entity(SDL_FPoint pos){}
Entity::~Entity() = default;

void Entity::update(){
   float delta_time = deltaTime();
   position.x += velocity.x * delta_time;
   position.y += velocity.y * delta_time;
   updateBound();

   rotation += rotation_speed;
}

void Entity::render(SDL_Renderer *renderer){
    if (!texture || !active) return;

    float w = src_rect.w * scale;
    float h = src_rect.h * scale;
    
    dst_rect = {
        position.x - w * 0.5f,
        position.y - h * 0.5f,
        w,
        h
    };

    SDL_RenderTextureRotated(renderer, texture, &src_rect, &dst_rect, rotation, nullptr, SDL_FLIP_NONE);
}

void Entity::updateBound(){
    float w = src_rect.w * scale;
    float h = src_rect.h * scale;
    bound = {
        position.x - w * 0.5f,
        position.y - h * 0.5f,
        w,
        h
    };
}

void Entity::onCollision(Entity *other){}

//Setters
void Entity::setTexture(SDL_Texture *tex, int x, int y, int width , int height){ 
    texture = tex;
    src_rect.x = x;
    src_rect.y = y;
    src_rect.w = width;
    src_rect.h = height;

    updateBound();

}

void Entity::setTextureList(std::vector<SDL_Texture*> tex_list){ texture_list = tex_list; }

void Entity::setPosition(SDL_FPoint pos){ position = pos; }
void Entity::setPosition(float x , float y){ position.x = x; position.y = y;}
void Entity::setPositionX(float x){ position.x = x;}
void Entity::setPositionY(float y){position.y = y;}

void Entity::setVelocity(SDL_FPoint vel){ velocity = vel; }
void Entity::setVelocity(float x, float y){ velocity.x = x; velocity.y = y;}
void Entity::setVelocityX(float x){ velocity.x = x; }
void Entity::setVelocityY(float y){ velocity.y = y; }

void Entity::setRotation(float rot){ rotation = rot; }
void Entity::setRotationSpeed(float rot_speed) { rotation_speed = rot_speed;}
void Entity::setScale(float scl){ scale = scl; }

void Entity::setActive(bool act){ active = act; }

//Getters
SDL_FPoint Entity::getPosition(){ return position; }
float Entity::getPositionX(){ return position.x;}
float Entity::getPositionY(){ return position.y;}
SDL_FPoint Entity::getVelocity(){ return velocity; }
float Entity::getVelocityX() {return velocity.x;}
float Entity::getVelocityY() {return velocity.y;}
float Entity::getRotation(){ return rotation; }
float Entity::getRotationSpeed() { return rotation_speed;}
float Entity::getScale(){ return scale; }
SDL_Texture *Entity::getTexture(){ return texture; }
std::vector<SDL_Texture*> Entity::getTextureList(){ return texture_list;}
SDL_FRect Entity::getBound(){ return bound; }
SDL_FRect Entity::getSrcRect(){ return src_rect;}
SDL_FRect Entity::getDstRect(){ return dst_rect; }
bool Entity::getActive(){ return active;}

int Entity::getHeight(){ return static_cast<int>(src_rect.h); }
int Entity::getWidth(){ return static_cast<int>(src_rect.w); }

