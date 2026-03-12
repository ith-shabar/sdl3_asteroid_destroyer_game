#include "bulletmanager.h"
#include "variables.h"

#include "../core/time.h"

void BulletManager::update(){
    for (auto * bullet  :entities) {
        if (!bullet->active) continue;


        // check for off screen bullet
        if (bullet->getPositionX() > SCREEN_WIDTH ||  bullet->getPositionX() < 0 
        || bullet->getPositionY() > SCREEN_HEIGHT || bullet->getPositionY() < 0) {
            bullet->setActive(false); 
        }
    }

    cleanUp();
}
