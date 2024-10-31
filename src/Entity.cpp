#include <Entity.hpp>
#include "Texture.hpp"
#include "Utils.hpp"
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
        >> ptrArchetypes
        ) : ptrArchetypes(ptrArchetypes), components(MAXCOMPONENTS) {
    this->ID = ++counter;
    this->texture = std::make_unique<Texture>();
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
