#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <Texture.hpp>
#include <cstddef>
#include <iostream>


Texture::Texture(){}
Texture::~Texture(){
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

int Texture::load_from_file(SDL_Renderer *renderer, const char *pathFile){
    SDL_Surface *tmpSurface = IMG_Load(pathFile);
    if (tmpSurface){
        texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
        SDL_FreeSurface(tmpSurface);

        if (!texture) {
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
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}
