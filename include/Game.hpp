#pragma once
#include "Entity.hpp"
#include <Enemy.hpp>
#include <System.hpp>
#include "Map.hpp"
#include <utils.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <Texture.hpp>
#include <GameObject.hpp>
#include <bitset>
#include <memory>
#include <unordered_map>
#include <vector>


class Game {
    public:
        Game();
        ~Game();

        void handleEvents();
        int init(const char* title, int x, int y, int width, int height, bool fullscreen);
        void update(float deltaTime);
        void render();
        void clean();

        bool running() { return isRunning; };
        
        std::shared_ptr<std::unordered_map<ComponentBitset, std::vector<std::shared_ptr<Entity>>, BitsetHash>> ptrArchetypes;

        static SDL_Renderer *renderer;

    private:
        bool isRunning;
        SDL_Window *window;

        Map *map = nullptr;
        Texture *texture_background = nullptr;
        std::shared_ptr<Entity> entidad;
        std::shared_ptr<Enemy>  enemy;
        std::unique_ptr<MovementSystem> movementSystem;
};

