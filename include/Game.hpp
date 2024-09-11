#pragma once
#include "Map.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <Texture.hpp>
#include <GameObject.hpp>

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
        
        const int MAX_FPS = 64;

        static SDL_Renderer *renderer;

    private:
        bool isRunning;
        SDL_Window *window;

        Map *map = nullptr;
        Texture *texture_background = nullptr;
        GameObject *player = nullptr;
        GameObject *enemy = nullptr;
};

