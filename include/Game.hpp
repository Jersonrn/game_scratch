#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

class Game {
    public:
        Game();
        ~Game();

        void handleEvents();
        void init(const char* title, int x, int y, int width, int height, bool fullscreen);
        void update();
        void render();
        void clean();

        bool running() { return isRunning; };

    private:
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;
};

