#include "Game.hpp"
#include <SDL2/SDL_video.h>


Game *game = nullptr;

int main() {
    game = new Game();

    game->init(
            "GameTEST",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            1280,
            720,
            false
    );

    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();

    return 0;
};
