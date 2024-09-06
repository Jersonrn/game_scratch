#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>


class Texture {
    public:
        Texture();
        ~Texture();
        int load_from_file(SDL_Renderer *renderer, const char *pathFile);
        void render(SDL_Renderer *renderer);

        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

    private:
};
