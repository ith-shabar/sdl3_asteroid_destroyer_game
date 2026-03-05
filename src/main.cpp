#include "core/app.h"
#include "core/entity.h"
#include "core/time.h"
#include <stdint.h>

int main(int argc, char *argv[])
{               
    App app;
    if (app.init() != 0) return 1;
    if (app.renderWindow("testing", 700, 700, 0) != 0)  return 1;

    SDL_Texture *tex = app.createTextureFromSurface("assets/player.png");

    Entity player;
    player.setTexture(tex,0, 0, 24, 24);
    player.setPosition(100,100);

    player.setVelocity(90,0);

    int running = 1;
    SDL_Event event;
    while (running) {
        uint64_t time = getTime();
        updateTime(); 
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }

        app.renderClear();
        player.render(app.getRenderer());
        player.update();
        app.display();
        setFPS(time);
    }
    return 0;
}
