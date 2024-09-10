#pragma  once
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <string>


class Texture {
    public:
        Texture();
        ~Texture();
        int load_from_file(
                const std::string &pathFile,
                int srcRectX = 0, int srcRectY = 0, int srcRectW = -1, int srcRectH = -1,
                int dstRectX = 0, int dstRectY = 0, int dstRectW = -1, int dstRectH = -1
                );
        void render();

        // getters
        float getXPosition() const ;
        float getYPosition() const;
        float getXScale() const;
        float getYScale() const;

        // setters
        void setXPosition(float x);
        void setYPosition(float y);
        void setXScale(float x);
        void setYScale(float y);

        void move(float x, float y);


    private:
        SDL_Texture *texture;
        SDL_Rect srcRect, dstRect;
};
