#include <Entity.hpp>
#include "Texture.hpp"
#include "utils.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>



Entity::Entity(
        std::shared_ptr<std::unordered_map<
            ComponentBitset,
            std::vector<std::shared_ptr<Entity>>,
            BitsetHash
        >> ptrArchetypes,
        const std::string &pathFile,
        float xPos, float yPos,
        float xScale, float yScale,
        int srcRectX, int srcRectY, int srcRectW, int srcRectH
        ) : ptrArchetypes(ptrArchetypes), components(MAXCOMPONENTS) {
    this->ID = ++counter;
    this->texture = std::make_unique<Texture>();
    /* this->texture->load_from_file(pathFile, srcRectX, srcRectY, srcRectW, srcRectH, xPos, yPos, srcRectW * xScale, srcRectH * yScale); */
}

Entity::~Entity(){}

void Entity::handleInputEvents(const SDL_KeyboardEvent& keyEvent) {};

std::size_t Entity::getID() { return this->ID; }

bool Entity::isActive() { return this->active; }

void Entity::destroy() { this->active = false; }

void Entity::render() { this->texture->render(); }

void Entity::updatePosition(float deltaTime) {
    Position *positionComponent = getComponent<Position>();
    Velocity *velocityComponent = getComponent<Velocity>();

    float posX = positionComponent->getX();
    float posY = positionComponent->getY();

    posX += velocityComponent->x * deltaTime;
    posY += velocityComponent->y * deltaTime;

    positionComponent->update(posX, posY);
}
