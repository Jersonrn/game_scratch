#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <cstddef>
#include <iostream>
#include "Game.hpp"
#include <GameObject.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <ostream>


Game::Game(){
}
Game::~Game(){
}

int Game::init(const char *title, int x, int y, int width, int height, bool fullscreen){
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0 ){
        Uint32 flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

        window = SDL_CreateWindow(title, x, y, width, height, flags);
        if (window == NULL) {
            std::cerr << "Window failed to init. Error: " <<SDL_GetError() << std::endl;
            return -1;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer){
            std::cout << "Renderer created!" << std::endl;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        } else {
            std::cerr << "Renderer failed to init. Error: " <<SDL_GetError() << std::endl;
            return -1;
        }

        texture_background = new Texture();
        texture_background->load_from_file(renderer, "res/tiles.webp");
        texture_background->setXScale(2);
        texture_background->setYScale(2);

        player = new GameObject( renderer, "res/robot.webp", 500, 100, 1, 1, 0, 0, 64, 64);

        // PLAYER
        // Player Texture
        SDL_Surface *tmpSurface = IMG_Load("res/robot.webp");
        if (tmpSurface) {
            playerTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
            SDL_FreeSurface(tmpSurface);

            if (!playerTexture) {
                std::cerr << "Failed to create player texture. Error: " << SDL_GetError() << std::endl;
            }
        } else {
            std::cerr << "Failed to load image. Error: " << IMG_GetError() << std::endl;
        }
        playerPositionX = 50;
        playerPositionY = 100;
        // Player Rectangle
        srcR.x = currentFrame * SPRITE_WIDTH; // frame position
        srcR.y = 0; // Row
        srcR.w = SPRITE_WIDTH;
        srcR.h = SPRITE_HEIGHT;

        destR.x = playerPositionX;
        destR.y = playerPositionY;
        destR.w = SPRITE_WIDTH;
        destR.h = SPRITE_HEIGHT;

        isRunning = true;
    } else {
        isRunning = false;
        return -1;
    }

    return 0;
}

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

void Game::update(float deltaTime){ }

void Game::render(){
    SDL_RenderClear(renderer);
    //this is where we would add stuff to render
    if (texture_background) {
        texture_background->render(renderer);
    }
    if (player) {
        player->render();
    }
    SDL_RenderCopy(renderer, playerTexture, &srcR, &destR);
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    if (texture_background) { delete texture_background; }
    if (playerTexture){ SDL_DestroyTexture(playerTexture); }
    if (player) { delete player; }
    IMG_Quit();
    SDL_Quit();
    std::cout << "Game Cleanned" << std::endl;
}
