#include "Game.hpp"
#include "GameObject.hpp"
#include <DynamicObject.hpp>


DynamicObject::DynamicObject(
        const std::string &pathFile,
        float xPos, float yPos,
        float xScale_, float yScale_,
        int srcRectX, int srcRectY, int srcRectW, int srcRectH 
        ): GameObject(pathFile, xPos, yPos, xScale_, yScale_, srcRectX, srcRectY, srcRectW, srcRectH) {
    this->setDirection(0., 0.);
    this->setVelocity(0., 0.);
}

DynamicObject::~DynamicObject() {}


void DynamicObject::update(float deltaTime) {


    //APPLY GRAVITY
    float gravityInPixelsPerSecondSquared = (Game::GRAVITY_ACCELERATION * Game::PIXELS_PER_METER);
    float verticalMovement = gravityInPixelsPerSecondSquared * deltaTime;
    GameObject::move(0., verticalMovement);
}

void DynamicObject::move(float x, float y) {
    // TODO: Maybe some calculations should go here

    GameObject::move(x, y);
}

void DynamicObject::setVelocity(float x, float y) {
    this->xVelocity = x;
    this->yVelocity = y;
}

void DynamicObject::setDirection(float x, float y) {
    this->xDirection = x;
    this->yDirection = y;
}
