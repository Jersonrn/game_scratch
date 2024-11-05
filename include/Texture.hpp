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
        void update();

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
        void setXCrop(float from, float to);
        void setYCrop(float from, float to);

        /**
         * @brief Sets the flip type of the texture.
         *
         * This function configures the flip type of the texture based on the
         * provided parameter. It accepts the following values:
         * - "NONE": No flipping applied.
         * - "HORIZONTAL": Horizontal flipping applied.
         * - "VERTICAL": Vertical flipping applied.
         *
         * @param flipType The flip type to apply.
         */
        void setFlip(std::string flipType);

        void move(float x, float y);


    private:
        SDL_Texture *texture;
        SDL_Rect srcRect, dstRect;
        double angle = 0;
        /* SDL_Point center; */
        SDL_RendererFlip flip = SDL_FLIP_NONE;
};
