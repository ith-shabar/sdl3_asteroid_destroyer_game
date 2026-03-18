#include "core/app.h"
#include "core/time.h"
#include "game/bullet.h"
#include "game/player.h"
#include "game/asteroid.h"
#include "game/variables.h"
#include <vector>

int main(int argc, char *argv[])
{               
    App app;
    app.init();
    app.renderWindow("astdst", SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    texture *player_tex = app.createTextureFromSurface("assets/player.png");
    texture *player_moving_tex = app.createTextureFromSurface("assets/playermoving.png");
    std::vector<SDL_Texture*> player_tex_list = {player_tex, player_moving_tex};
    texture *bullet_tex = app.createTextureFromSurface("assets/bullet.png");
    texture *asteroid01_tex = app.createTextureFromSurface("assets/asteroid01.png");
    texture *asteroid02_tex = app.createTextureFromSurface("assets/asteroid02.png");
    texture *asteroid03_tex = app.createTextureFromSurface("assets/asteroid03.png");
    texture *asteroid04_tex = app.createTextureFromSurface("assets/asteroid04.png");
    texture *asteroid05_tex = app.createTextureFromSurface("assets/asteroid05.png");
    std::vector<SDL_Texture*> asteroid_tex = {asteroid01_tex, asteroid02_tex, asteroid03_tex, asteroid04_tex, asteroid05_tex};

    texture *start_ui = app.createTextureFromSurface("assets/start.png");
    texture *game_over_ui = app.createTextureFromSurface("assets/gameover.png");

    Player player;
    player.setTexture(player_tex,0, 0, 24, 24);
    player.setTextureList(player_tex_list);
    player.setPosition(500,450);
    player.setBulletTex(bullet_tex);

    Bullet bullets;
    bullets.setTexture(bullet_tex, 0, 0, 3, 6);

    Asteroid asteroid;
    asteroid.setTextureList(asteroid_tex);

    mode = start;

    SDL_Event event;
    while (game_running) {

        switch (mode) {
            case start:

                break;
            case game:

                break;
            case result:

                break;

        }
        updateTime(); 
        uint64_t start_time = getTime();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) game_running = 0;
            player.handleInput(event);
        }
        
        //update
        player.update();
        asteroid.update();

        //collision
        //bullet vs asteroid
        for (auto *bullets : player.getBulletManager().getEntities()) {
            for (auto *asteroids : asteroid.getAsteroidManager().getEntities()) {
                 asteroids->checkCollision(bullets);
            }
        }
        // asteroid vs player
        for (auto *ast : asteroid.getAsteroidManager().getEntities()) {
            player.checkCollision(ast);
        }


        // asteroid vs asteroid
        auto asteroids = asteroid.getAsteroidManager().getEntities();
        for (size_t i = 0; i < asteroids.size(); i++) {
            for (size_t j = i + 1; j < asteroids.size(); j++) {
                asteroids[i]->checkCollision(asteroids[j]);
            }
        }



        //render
        app.renderClear();
        player.render(app.getRenderer());
        asteroid.render(app.getRenderer());

        app.display();

        capFPS(start_time);
    }
    return 0;
}
