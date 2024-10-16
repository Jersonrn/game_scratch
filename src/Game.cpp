#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <cstddef>
#include <iostream>

#include "Game.hpp"
#include "DynamicObject.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "utils.hpp"
#include <GameObject.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <memory>
#include <ostream>
#include <unordered_map>
#include <vector>


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

        this->ptrArchetypes = std::make_shared<std::unordered_map<ComponentBitset, std::vector<std::shared_ptr<Entity>>, BitsetHash>>();

        this->texture_background = new Texture();
        this->texture_background->load_from_file("res/tiles.webp");

        this->map = new Map();
        this->map->loadFromFile("res/map/map.txt");

        this->movementSystem = std::make_unique<MovementSystem>(this->ptrArchetypes);

        this->entidad = std::make_shared<Entity>(this->ptrArchetypes, "res/enemy.webp", 500, 150, 1, 1, 0, 0, 128, 128);
        this->entidad->addComponent<Velocity>(0., 100.);
        this->entidad->addComponent<Position>(400., 9.);
        this->entidad->addComponent<Render>();


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

    this->movementSystem->update(deltaTime);
}

void Game::render(){
    SDL_RenderClear(this->renderer);

    if (this->map) { this->map->render(); }

    for (const auto &e : (*this->ptrArchetypes)[getComponentBitset<Render>()]) {
        e->render();
    }

    SDL_RenderPresent(this->renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(this->renderer);

    if (this->texture_background) { delete this->texture_background; }
    if (this->map) { delete this->map; }

    IMG_Quit();
    SDL_Quit();
    std::cout << "Game Cleanned" << std::endl;
}
