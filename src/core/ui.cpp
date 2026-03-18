#include "ui.h"
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_rect.h>
#include <cstdio>

Ui::Ui(SDL_FPoint pos) { position = pos; }
Ui::~Ui() { }

void Ui::update() { 

    updateBound();
}

void Ui::render(SDL_Renderer *renderer) {

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

void Ui::checkHover(){
    float x , y;
    SDL_GetMouseState(&x, &y);
    SDL_FRect mouse_rect = {x ,y ,1.0f, 1.0f};

    if (SDL_HasRectIntersectionFloat(&bound, &mouse_rect)) { onHover(&mouse_rect); }

}

void Ui::checkClick(){
    float x , y;
    SDL_GetMouseState(&x, &y);
    SDL_FRect mouse_rect = {x ,y ,1.0f, 1.0f};

    if (SDL_HasRectIntersectionFloat(&bound, &mouse_rect) == SDL_BUTTON_LMASK) { onClick(&mouse_rect); printf("pressed"); }

}
void Ui::updateBound() { 

    float w = src_rect.w * scale;
    float h = src_rect.h * scale;
    bound = {
        position.x - w * 0.5f,
        position.y - h * 0.5f,
        w,
        h
    };
}

void Ui::setTexture(SDL_Texture *tex, int x, int y, int width, int height) {

    texture = tex;
    src_rect.x = x;
    src_rect.y = y;
    src_rect.w = width;
    src_rect.h = height;

    updateBound();

}

void Ui::setPosition(SDL_FPoint pos) { position = pos;}
void Ui::setPosition(float x, float y) { position.x = x; position.y = y; }
void Ui::setPositionX(float x) { position.x = x; }
void Ui::setPositionY(float y) { position.y = y; }
void Ui::setRotation(float rot) { rotation = rot; }
void Ui::setScale(float scl) { scale = scl; }
void Ui::setActive(bool act) { active = act;}

SDL_FPoint Ui::getPosition() { return position; }
float Ui::getPositionX() { return position.x; }
float Ui::getPositionY() { return position.y; }
float Ui::getRotation() { return rotation; }
float Ui::getScale() { return scale; }
SDL_Texture *Ui::getTexture() { return texture; }
SDL_FRect Ui::getBound() { return bound; }
SDL_FRect Ui::getSrcRect() { return src_rect; }
SDL_FRect Ui::getDstRect() { return dst_rect; }
bool Ui::getActive() { return active; }
int Ui::getTypeID() const { return type_id; }
int Ui::getHeight() { return static_cast<int>(dst_rect.h); }
int Ui::getWidth() { return static_cast<int>(dst_rect.w); }
