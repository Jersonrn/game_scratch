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


SDL_Renderer* Game::renderer = nullptr;

Game::Game(){
}
Game::~Game(){
}

int Game::init(const char *title, int x, int y, int width, int height, bool fullscreen){
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0 ){
        Uint32 flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

        this->window = SDL_CreateWindow(title, x, y, width, height, flags);
        if (this->window == NULL) {
            std::cerr << "Window failed to init. Error: " <<SDL_GetError() << std::endl;
            return -1;
        }

        this->renderer = SDL_CreateRenderer(this->window, -1, 0);
        if (this->renderer){
            std::cout << "Renderer created!" << std::endl;
            SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
        } else {
            std::cerr << "Renderer failed to init. Error: " <<SDL_GetError() << std::endl;
            return -1;
        }

        this->texture_background = new Texture();
        this->texture_background->load_from_file("res/tiles.webp");

        this->player = new GameObject("res/robot.webp", 500, 100, 1, 1, 0, 0, 64, 64);
        this->enemy = new GameObject("res/enemy.webp", 500, 150, 1, 1, 0, 0, 128, 128);


        this->isRunning = true;
    } else {
        this->isRunning = false;
        return -1;
    }

    return 0;
}

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_QUIT:
            this->isRunning = false;
            break;

        default:
            break;
    }
}

void Game::update(float deltaTime){


    // apply gravity
    this->player->move(0, (32*9.8)*deltaTime);
    this->enemy->move(0, (32*9.8)*deltaTime);
}

void Game::render(){
    SDL_RenderClear(this->renderer);
    //this is where we would add stuff to render
    if (this->texture_background) { this->texture_background->render(); }

    if (this->player) { this->player->render(); }
    if (this->enemy) { this->enemy->render(); }

    SDL_RenderPresent(this->renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(this->renderer);

    if (this->texture_background) { delete this->texture_background; }
    if (this->player) { delete this->player; }
    if (this->enemy) { delete this->enemy; }

    IMG_Quit();
    SDL_Quit();
    std::cout << "Game Cleanned" << std::endl;
}
