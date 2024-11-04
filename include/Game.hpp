#pragma once
#include "Entity.hpp"
#include <Enemy.hpp>
#include <Player.hpp>
#include <System.hpp>
#include "Map.hpp"
#include <Utils.hpp>

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
        int init(const char* title, int x, int y, int width, int height, bool fullscreen, bool showCols);
        void update(float deltaTime);
        void render();
        void clean();

        bool running() { return isRunning; };
        
        std::shared_ptr<std::unordered_map<ComponentBitset, std::vector<std::shared_ptr<Entity>>, BitsetHash>> ptrArchetypes;

        static SDL_Renderer *renderer;

    private:
        bool isRunning;
        SDL_Window *window;

        bool renderCollision;

        Map *map = nullptr;
        Texture *tiles = nullptr;
        std::shared_ptr<Enemy>  enemy;
        std::shared_ptr<Player>  player;
        std::unique_ptr<MovementSystem> movementSystem;
};

