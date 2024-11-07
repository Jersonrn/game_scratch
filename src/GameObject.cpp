#include "Game.hpp"
#include "Texture.hpp"
#include <GameObject.hpp>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <memory>


GameObject::GameObject(
        const std::string &pathFile,
        float xPos, float yPos,
        float xScale_, float yScale_,
        int srcRectX, int srcRectY, int srcRectW, int srcRectH )
    : texture(nullptr) {

        if (!Game::renderer) {
            std::cerr << "Renderer is null" << std::endl;
        }

        texture = new Texture();
        texture->load_from_file(
                pathFile,
                srcRectX, srcRectY, srcRectW, srcRectH,
                /* xPos, yPos, srcRectW * xScale_, srcRectH * yScale_ */
                xPos, yPos, xScale_, yScale_
        );

}

GameObject::~GameObject() {
    if (texture) {
        delete texture;
    }
}

void GameObject::update(float deltaTime) {}

void GameObject::render() {
    this->texture->render();
}


// getters
float GameObject::getXPosition() const { return this->texture->getXPosition(); }
float GameObject::getYPosition() const { return this->texture->getYPosition(); }
float GameObject::getXScale() const { return this->texture->getXScale(); }
float GameObject::getYScale() const { return this->texture->getYScale(); }

// setters
void GameObject::setXPosition( float x ) {
    this->texture->setXPosition(x);
}
void GameObject::setYPosition( float y ) {
    this->texture->setYPosition(y);
}
void GameObject::setXScale( float x ) {
    this->texture->setXScale(x);
}
void GameObject::setYScale( float y ) {
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
    this->texture->move(x, y);
}
