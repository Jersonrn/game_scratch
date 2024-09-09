#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <Texture.hpp>
#include <iostream>
#include <string>


Texture::Texture() : texture(nullptr), srcRect{ 0, 0, 32, 32 }, dstRect{ 0, 0, 32, 32 }{}
Texture::~Texture(){
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

int Texture::load_from_file(
        SDL_Renderer *renderer, const std::string &pathFile,
        int srcRectX, int srcRectY, int srcRectW, int srcRectH,
        int dstRectX, int dstRectY, int dstRectW, int dstRectH) {

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
            SDL_QueryTexture(texture, nullptr, nullptr, dstRectW == -1 ? &dstRectW : nullptr, dstRectH == -1 ? &dstRectH : nullptr);

            srcRect = { srcRectX, srcRectY, srcRectW, srcRectH };
            dstRect = { dstRectX, dstRectY, dstRectW, dstRectH };

        } else {
            std::cerr << "Failed to create texture. Error: " << SDL_GetError() << std::endl;
            return -1;
        }

    } else {
        std::cerr << "Failed to load image. Error: " << IMG_GetError() << std::endl;
        return -1;
    }


    std::cout << "Texture created successfully" << std::endl;
    return 0;
}

void Texture::render(SDL_Renderer *renderer){
    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}

// getters
float Texture::getXPosition() const { return dstRect.x; }
float Texture::getYPosition() const { return dstRect.y; }
float Texture::getXScale() const { return dstRect.w; }
float Texture::getYScale() const { return dstRect.h; }

// setters
void Texture::setXPosition(float x) { this->dstRect.x = x; }
void Texture::setYPosition(float y) { this->dstRect.y = y; }
void Texture::setXScale(float x) {
    this->dstRect.w = this->srcRect.w * x;
}
void Texture::setYScale(float y) {
    this->dstRect.h = this->srcRect.h * y;
}
