#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <cstddef>
#include <iostream>
#include <memory>
#include "Game.hpp"
#include <SDL2/SDL_video.h>
#include <utils.hpp>


std::size_t Entity::counter = 0;

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

    const Uint32 FRAME_DELAY = 1000 / MAX_FPS;
    Uint32 lastFrameTime = SDL_GetTicks();

    while (game->running()) {
        Uint32 frameStart = SDL_GetTicks();

        game->handleEvents();

        Uint32 currentFrameTime = SDL_GetTicks();
        float deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentFrameTime;

        game->update(deltaTime);
        game->render();

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY) { SDL_Delay(FRAME_DELAY - frameTime); }
    }

    game->clean();

    return 0;
};
