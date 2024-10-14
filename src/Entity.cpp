#include "Entity.hpp"
#include "utils.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
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
}

Entity::~Entity(){}


std::size_t Entity::getID() { return this->ID; }

bool Entity::isActive() { return this->active; }

void Entity::destroy() { this->active = false; }
