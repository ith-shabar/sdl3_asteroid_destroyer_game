#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SDL3/SDL.h>
#include <algorithm>
#include <cstddef>
#include <vector>

template<typename T>
class UiManager{
    protected:
        std::vector<T*> uis;

    public:
        virtual ~UiManager(){ clear(); }

        //add ui
        void add(T* ui){ uis.push_back(ui); }

        //remove
        void remove(T* ui){
            auto it = std::find(uis.begin(), uis.end(), ui);
            if (it != uis.end()) {
                delete *it;
                uierase(it);
            }
        }
       
        //remove at index
        void removeAt(size_t index){
            if (index < uis.size()) {
                delete uis[index];
                uis.erase(uis.begin() + index);

            }
        }
       
        // delete ui
        void clear(){
            for (auto *ui : uis) { delete ui; }

            uis.clear();
        }

        // cleanup ui that are not active
        void cleanUp(){
            uis.erase(
                std::remove_if(uis.begin(), uis.end(), [](T* e) {
                    if (!e->active) {
                        delete e;
                        return true;
                    }
                        return false;
                    }),
                    uis.end()
                );
        }

        virtual void update(){
            for (auto* ui : uis) { 
                if (ui->active) ui->update(); 
            }
        }

        virtual void render(SDL_Renderer * renderer){
            for (auto* ui : uis) { 
                if (ui->active) ui->render(renderer); 
            }
        }

        //some getters
        std::vector<T*> getui(){ return uis;}

        size_t size() const { return uis.size(); }
        bool empty() const { return uis.empty();}

};

#endif 
