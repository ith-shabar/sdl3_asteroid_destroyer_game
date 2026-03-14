#include "core/app.h"
#include "core/time.h"
#include "game/player.h"
#include "game/asteroid.h"
#include "game/variables.h"
#include <vector>

int main(int argc, char *argv[])
{               
    App app;
    app.init();
    app.renderWindow("testing", SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    texture *player_tex = app.createTextureFromSurface("assets/player.png");
    texture *bullet_tex = app.createTextureFromSurface("assets/bullet.png");
    texture *asteroid01_tex = app.createTextureFromSurface("assets/asteroid01.png");
    texture *asteroid02_tex = app.createTextureFromSurface("assets/asteroid02.png");
    texture *asteroid03_tex = app.createTextureFromSurface("assets/asteroid03.png");
    std::vector<SDL_Texture*> asteroid_tex = {asteroid01_tex, asteroid02_tex, asteroid03_tex};

    Player player;
    player.setTexture(player_tex,0, 0, 24, 24);
    player.setPosition(500,450);
    player.setBulletTex(bullet_tex);

    Asteroid asteroid;
    asteroid.setTextureList(asteroid_tex);

    SDL_Event event;
    while (game_running) {

        uint64_t start_time = getTime();
        updateTime(); 

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) game_running = 0;
            player.handleInput(event);
        }

        app.renderClear();
        player.render(app.getRenderer());
        asteroid.render(app.getRenderer());
        player.update();
        asteroid.update();
        app.display();

        capFPS(start_time);
    }
    return 0;
}
