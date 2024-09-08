#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <Texture.hpp>
#include <iostream>
#include <string>


Texture::Texture() : texture(nullptr), srcRect{ 0, 0, 32, 32 }, destRect{ 0, 0, 32, 32 }{}
Texture::~Texture(){
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

int Texture::load_from_file(
        SDL_Renderer *renderer, const std::string &pathFile,
        int srcRectX, int srcRectY, int srcRectW, int srcRectH,
        int destRectX, int destRectY, int destRectW, int destRectH) {

    if (!renderer) {
        std::cerr << "Renderer is null" << std::endl;
        return -1;
    }

    SDL_Surface *tmpSurface = IMG_Load(pathFile.c_str());
    if (tmpSurface){
        texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
        SDL_FreeSurface(tmpSurface);

        if (texture) {
            SDL_QueryTexture(texture, nullptr, nullptr, srcRectW == -1 ? &srcRectW : nullptr, srcRectH == -1 ? &srcRectH : nullptr);
            SDL_QueryTexture(texture, nullptr, nullptr, destRectW == -1 ? &destRectW : nullptr, destRectH == -1 ? &destRectH : nullptr);

            srcRect = { srcRectX, srcRectY, srcRectW, srcRectH };
            destRect = { destRectX, destRectY, destRectW, destRectH };

        } else {
            std::cerr << "Failed to create texture. Error: " << SDL_GetError() << std::endl;
            return -1;
        }

    } else {
        std::cerr << "Failed to load image. Error: " << IMG_GetError() << std::endl;
        return -1;
    }


    return 0;
}

void Texture::render(SDL_Renderer *renderer){
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}

// getters
float Texture::getXPosition() const { return destRect.x; }
float Texture::getYPosition() const { return destRect.y; }
float Texture::getXScale() const { return destRect.w; }
float Texture::getYScale() const { return destRect.h; }

// setters
void Texture::setXPosition(float x) { this->destRect.x = x; }
void Texture::setYPosition(float y) { this->destRect.y = y; }
void Texture::setXScale(float x) {
    int originalScaleX;

    SDL_QueryTexture(this->texture, nullptr, nullptr, &originalScaleX, nullptr);
    int newXScale = originalScaleX * x;

    this->destRect.w = newXScale;
}
void Texture::setYScale(float y) {
    int originalScaleY;

    SDL_QueryTexture(this->texture, nullptr, nullptr, nullptr, &originalScaleY);
    int newXScale = originalScaleY * y;

    this->destRect.h = newXScale;
}
