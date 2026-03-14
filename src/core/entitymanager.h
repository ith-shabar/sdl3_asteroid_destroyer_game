#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <SDL3/SDL.h>
#include <algorithm>
#include <cstddef>
#include <vector>

template<typename T>
class EntityManager{
    protected:
        std::vector<T*> entities;

    public:
        virtual ~EntityManager(){ clear(); }

        //add entity
        void add(T* entity){ entities.push_back(entity); }

        //remove
        void remove(T* entity){
            auto it = std::find(entities.begin(), entities.end(), entity);
            if (it != entities.end()) {
                delete *it;
                entities.erase(it);
            }
        }
       
        //remove at index
        void removeAt(size_t index){
            if (index < entities.size()) {
                delete entities[index];
                entities.erase(entities.begin() + index);
            }
        }
       
        // delete entities
        void clear(){
            for (auto *entity : entities) { delete entity; }

            entities.clear();
        }

        // cleanup entities that are not active
        void cleanUp(){
            entities.erase(
                std::remove_if(entities.begin(), entities.end(), [](T* e) {
                    if (!e->active) {
                        delete e;
                        return true;
                    }
                        return false;
                    }),
                    entities.end()
                );
        }

        virtual void update(){
            for (auto* entity : entities) { 
                if (entity->active) entity->update(); 
            }
        }

        virtual void render(SDL_Renderer * renderer){
            for (auto* entity : entities) { 
                if (entity->active) entity->render(renderer); 
            }
        }

        //some getters
        std::vector<T*> getEntities(){ return entities;}

        size_t size() const { return entities.size(); }
        bool empty() const { return entities.empty();}

};


#endif // !ENTITYMANAGER_H
