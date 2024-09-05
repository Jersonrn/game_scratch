#include <iostream>
#include <memory>
#include "Game.hpp"
#include <SDL2/SDL_video.h>


int main() {
    std::unique_ptr<Game> game = std::make_unique<Game>();

    if (game->init(
            "GameTEST",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            1280,
            720,
            false
            ) != 0) {
        std::cerr << "Error initializing game." <<SDL_GetError() << std::endl;
        return -1;
    };

    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();

    return 0;
};
