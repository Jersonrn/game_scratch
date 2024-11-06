#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <cstddef>
#include <iostream>

#include "Game.hpp"
#include "Component.hpp"
#include "DynamicObject.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "Utils.hpp"
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

int Game::init(const char *title, int x, int y, int width, int height, bool fullscreen, bool showCols) {
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

        this->renderCollision = showCols;

        this->ptrArchetypes = std::make_shared<std::unordered_map<ComponentBitset, std::vector<std::shared_ptr<Entity>>, BitsetHash>>();

        this->tiles = new Texture();
        this->tiles->load_from_file("res/tiles.webp");

        this->map = new Map();
        this->map->loadBlocksFromFile("res/map/map.txt");
        this->map->loadObjectsFromJSONFile("res/map/objs.json");

        this->movementSystem = std::make_unique<MovementSystem>(this->ptrArchetypes);

        this->enemy = std::make_shared<Enemy>(this->ptrArchetypes);
        this->enemy->initialize();

        this->player = std::make_shared<Player>(this->ptrArchetypes);
        this->player->initialize();


        this->isRunning = true;
    } else {
        this->isRunning = false;
        return -1;
    }

    return 0;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) { // Process all available events
        switch (event.type) {
            case SDL_QUIT:
                this->isRunning = false;
                break;

            // Manage events (keys, mouse, etc)
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    this->isRunning = false;
                } 
                break;

            default:
                break;
        }
        for (const auto& e : (*this->ptrArchetypes)[getComponentBitset<InputKey>()]) {
            e->getComponent<InputKey>()->update(event);
        };
    }
}

void Game::update(float deltaTime){

    this->movementSystem->update(deltaTime);
    for (const auto &e:(*this->ptrArchetypes)[getComponentBitset<Animator>()] ) {
        e->getComponent<Animator>()->update(deltaTime);
    }
}

void Game::render(){
    SDL_RenderClear(this->renderer);

    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);

    if (this->map) { this->map->render(); }

    for (const auto &e : (*this->ptrArchetypes)[getComponentBitset<Render>()]) {
        e->render();
    }

    if (this->renderCollision) {
        std::vector<std::shared_ptr<Entity>> colEntities = (*this->ptrArchetypes)[getComponentBitset<Collision>()];

        //RECT
        int n = colEntities.size();
        SDL_Rect rects[n];

        for(std::vector<std::shared_ptr<Entity>>::size_type i = 0; i != colEntities.size(); i++) {
            rects[i] = colEntities[i]->getComponent<Collision>()->colRect;
        }

        SDL_SetRenderDrawColor(this->renderer, 93, 197, 226, 255); // Blue Color
        SDL_RenderDrawRects(this->renderer, rects, n);

        //FILLRECT
        /* for (const auto& c : colEntities) { */
        /*     SDL_SetRenderDrawColor(this->renderer, 0, 0, 255, 100); */
        /*     SDL_RenderFillRect(this->renderer, &c->getComponent<Collision>()->colRect); */
        /* } */
    }

    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0); // Black Color

    SDL_RenderPresent(this->renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(this->renderer);

    if (this->tiles) { delete this->tiles; }
    if (this->map) { delete this->map; }

    IMG_Quit();
    SDL_Quit();
    std::cout << "Game Cleanned" << std::endl;
}
