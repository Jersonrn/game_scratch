#include "Texture.hpp"
#include <GameObject.hpp>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <memory>


GameObject::GameObject(
        SDL_Renderer *renderer, const std::string &pathFile,
        float xPos, float yPos,
        float xScale_, float yScale_,
        int srcRectX, int srcRectY, int srcRectW, int srcRectH )
    : renderer(renderer), texture(nullptr),
    xPosition(xPos), yPosition(yPos),
    xScale(xScale_), yScale(yScale_) {

        if (renderer) {
            this->renderer = renderer;
        } else {
            std::cerr << "Renderer is null" << std::endl;
        }

        texture = new Texture();
        texture->load_from_file(this->renderer, pathFile, srcRectX, srcRectY, srcRectW, srcRectH, this->xPosition, this->yPosition, srcRectW * xScale_, srcRectH * yScale_);

        this->setXScale(2);
        this->setYScale(2);
}

GameObject::~GameObject() {
    if (texture) {
        delete texture;
    }
}

void GameObject::update() {}

void GameObject::render() {
    this->texture->render(this->renderer);
}

