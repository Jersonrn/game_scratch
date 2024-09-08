#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <string>


class Texture {
    public:
        Texture();
        ~Texture();
        int load_from_file(
                SDL_Renderer *renderer, const std::string &pathFile,
                int srcRectX = 0, int srcRectY = 0, int srcRectW = -1, int srcRectH = -1,
                int destRectX = 0, int destRectY = 0, int destRectW = -1, int destRectH = -1
                );
        void render(SDL_Renderer *renderer);

        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

    private:
};
