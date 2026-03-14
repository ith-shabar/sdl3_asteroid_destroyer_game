#include "asteroidmanager.h"
#include "variables.h"

void AsteroidManager::update(){

    for (auto * asteroid  : entities) {
        if (!asteroid->active) continue;

        // update asteroids
        asteroid->update();

        // check for off screen asteroid
        // ....
    }

    cleanUp();
}
