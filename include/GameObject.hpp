#pragma once
#include <SDL2/SDL_render.h>
#include <Texture.hpp>
#include <memory>
#include <string>


class GameObject {
    public:
        GameObject(
                SDL_Renderer *renderer, const std::string &pathFile,
                float xPos = 0, float yPos = 0,
                float xScale_ = 1, float yScale_ = 1,
                int srcRectX = 0, int srcRectY = 0, int srcRectW = -1, int srcRectH = -1
                );
        ~GameObject();
        void update();
        void render();

        // getters
        float getXPosition() const { return xPosition; }
        float getYPosition() const { return yPosition; }
        float getXScale() const { return xScale; }
        float getYScale() const { return yScale; }
        
        // setters
        void setXPosition( float x ) {
            this->xPosition = x;
            this->texture->setXPosition(x);
        }
        void setYPosition( float y ) {
            this->yPosition = y;
            this->texture->setYPosition(y);
        }
        void setXScale( float x ) {
            this->xScale = x;
            this->texture->setXScale(x);
        }
        void setYScale( float y ) {
            this->yScale = y;
            this->texture->setYScale(y);
        }


    private:
        SDL_Renderer *renderer;
        /* std::shared_ptr<Texture> texture; */
        Texture *texture = nullptr;

        float xPosition;
        float yPosition;
        float xScale;
        float yScale;
};
