#include "asteroidmanager.h"
#include "variables.h"

void AsteroidManager::update(){
    const int off_screen_buffer = 100; // pixels
                                       //
    for (auto * asteroid  : entities) {
        if (!asteroid->active) continue;

        // update asteroids
        asteroid->update();

        // check for off screen asteroid
    if (asteroid->getPositionX() < -off_screen_buffer || 
        asteroid->getPositionX() > SCREEN_WIDTH + off_screen_buffer ||
        asteroid->getPositionY() < -off_screen_buffer || 
        asteroid->getPositionY() > SCREEN_HEIGHT + off_screen_buffer) { asteroid->setActive(false); }    
    }

    cleanUp();
}
