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


// getters
float GameObject::getXPosition() const { return xPosition; }
float GameObject::getYPosition() const { return yPosition; }
float GameObject::getXScale() const { return xScale; }
float GameObject::getYScale() const { return yScale; }

// setters
void GameObject::setXPosition( float x ) {
    this->xPosition = x;
    this->texture->setXPosition(x);
}
void GameObject::setYPosition( float y ) {
    this->yPosition = y;
    this->texture->setYPosition(y);
}
void GameObject::setXScale( float x ) {
    this->xScale = x;
    this->texture->setXScale(x);
}
void GameObject::setYScale( float y ) {
    this->yScale = y;
    this->texture->setYScale(y);
}

void GameObject::setPosition(float x, float y) {
    this->setXPosition(x);
    this->setYPosition(y);
}
void GameObject::setScale(float x, float y) {
    this->setXScale(x);
    this->setYScale(y);
}
void GameObject::move(float x, float y) {
    this->xPosition += x;
    this->yPosition += y;
    this->texture->move(x, y);
}
