#pragma once
#include <SDL2/SDL_render.h>
#include <Texture.hpp>
#include <memory>
#include <string>


class GameObject {
    public:
        GameObject(
                const std::string &pathFile,
                float xPos = 0, float yPos = 0,
                float xScale_ = 1, float yScale_ = 1,
                int srcRectX = 0, int srcRectY = 0, int srcRectW = -1, int srcRectH = -1
                );
        virtual ~GameObject();
        virtual void update(float deltaTime);
        void render();

        // getters
        float getXPosition() const;
        float getYPosition() const;
        float getXScale() const;
        float getYScale() const;
        
        // setters
        void setXPosition( float x );
        void setYPosition( float y );
        void setXScale( float x );
        void setYScale( float y );

        void setPosition(float x, float y);
        void setScale(float x, float y);

        virtual void move(float x, float y);

    private:
        /* std::shared_ptr<Texture> texture; */
        Texture *texture = nullptr;

        float xPosition;
        float yPosition;
        float xScale;
        float yScale;
};
