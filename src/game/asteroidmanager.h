#ifndef ASTEROIDMANAGER_H
#define ASTEROIDMANAGER_H

#include "../core/entitymanager.h"
#include "../core/entity.h"

class AsteroidManager : public EntityManager<Entity> {
    public:
        void update() override;

};

#endif // !ASTEROIDMANAGER_H
