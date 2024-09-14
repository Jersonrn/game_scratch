#pragma once
#include "DynamicObject.hpp"
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
        static constexpr float PIXELS_PER_METER = 32.f;
        static constexpr float GRAVITY_ACCELERATION = 9.8f;

        static SDL_Renderer *renderer;

    private:
        bool isRunning;
        SDL_Window *window;

        Map *map = nullptr;
        Texture *texture_background = nullptr;
        DynamicObject *player = nullptr;
        DynamicObject *enemy = nullptr;
};

