#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "../core/entity.h"
#include "../core/entitymanager.h"

class BulletManager : public EntityManager<Entity> {
    public:
        void update() override;


};

#endif

