#include "buttonui.h"
#include "variables.h"
#include "../core/audio.h"


void Button::update(){
    Ui::update();
    checkClick();
}

void Button::render(SDL_Renderer *renderer){
    Ui::render(renderer);
}

void Button::checkHover(){
    Ui::checkHover();
}

void Button::onHover(SDL_FRect *rect){}

void Button::checkClick(){
    Ui::checkClick();
}

void Button::onClick(SDL_FRect *rect){
    if (mode == start)  mode = game; 
    else if (mode == result)  mode = start;
    Audio::getInstance()->playSfx(0);
}
