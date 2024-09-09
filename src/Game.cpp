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

        player = new GameObject(renderer, "res/robot.webp", 500, 100, 1, 1, 0, 0, 64, 64);
        enemy = new GameObject(renderer, "res/enemy.webp", 500, 150, 1, 1, 0, 0, 128, 128);


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

void Game::update(float deltaTime){


    // apply gravity
    player->move(0, (32*9.8)*deltaTime);
    enemy->move(0, (32*9.8)*deltaTime);
}

void Game::render(){
    SDL_RenderClear(renderer);
    //this is where we would add stuff to render
    if (texture_background) { texture_background->render(renderer); }

    if (player) { player->render(); }
    if (enemy) { enemy->render(); }

    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    if (texture_background) { delete texture_background; }
    if (player) { delete player; }
    if (enemy) { delete enemy; }

    IMG_Quit();
    SDL_Quit();
    std::cout << "Game Cleanned" << std::endl;
}
