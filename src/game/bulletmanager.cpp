#include "bulletmanager.h"
#include "variables.h"

#include "../core/time.h"

void BulletManager::update(){
    float delta_time = deltaTime();
    for (auto * bullet  :entities) {
        if (!bullet->active) continue;

        // update bullets
        bullet->update();

        // check for off screen bullet
        if (bullet->getPositionX() > SCREEN_WIDTH ||  bullet->getPositionX() < 0 
        || bullet->getPositionY() > SCREEN_HEIGHT || bullet->getPositionY() < 0) {
            bullet->setActive(false); 
        }
    }

    cleanUp();
}
