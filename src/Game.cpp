#include <iostream>
#include "Game.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

Game::Game(){
}
Game::~Game(){
}

int Game::init(const char *title, int x, int y, int width, int height, bool fullscreen){
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0 ){
        Uint32 flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

        window = SDL_CreateWindow(title, x, y, width, height, flags);
        if (window == NULL) {
            std::cout << "Window failed to init. Error: " <<SDL_GetError() << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer){
            std::cout << "Renderer created!" << std::endl;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }

        isRunning = true;
    } else {
        isRunning = false;
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

void Game::update(){ }

void Game::render(){
    SDL_RenderClear(renderer);
    //this is where we would add stuff to render
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleanned" << std::endl;
}
