#include "Entity.hpp"
#include "utils.hpp"
#include <System.hpp>



System::System(
        std::shared_ptr<std::unordered_map<
            ComponentBitset,
            std::vector<std::shared_ptr<Entity>>,
            BitsetHash
        >> ptrArchetypes
        ) : ptrArchetypes(ptrArchetypes) {}
System::~System() {}

void System::update() {};
void System::update(float deltaTime) {};



//MovementSystem
MovementSystem::MovementSystem(
        std::shared_ptr<std::unordered_map<
            ComponentBitset,
            std::vector<std::shared_ptr<Entity>>,
            BitsetHash
        >> ptrArchetypes
        ) : System(ptrArchetypes) {};

MovementSystem::~MovementSystem(){};

void MovementSystem::update(){};

void MovementSystem::update(float deltaTime) {
    ComponentBitset bitset = getComponentBitset<Position>() | getComponentBitset<Velocity>();
    for (const auto &e : (*this->ptrArchetypes)[bitset]) {
        e->updatePosition(deltaTime);
    }
}


