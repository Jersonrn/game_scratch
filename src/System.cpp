#include "Entity.hpp"
#include "utils.hpp"
#include <SDL2/SDL_rect.h>
#include <System.hpp>
#include <array>
#include <iostream>



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
        Position* posComponent = e->getComponent<Position>();
        float xPos = posComponent->getX();
        float yPos = posComponent->getY();

        e->updatePosition(deltaTime);

        if (e->hasComponent<Collision>()) {
            Collision* colComponent = e->getComponent<Collision>();
            colComponent->update();

            ComponentBitset colBitset = getComponentBitset<Collision>();
            for (const auto& colEntity : (*this->ptrArchetypes)[colBitset]) {
                if (colEntity->getID() != e->getID()) {
                    SDL_Rect* B = colEntity->getComponent<Collision>()->getRect();

                    std::array<bool, 2> collision = colComponent->hasCollision(B);

                    if (collision[0]) {
                        posComponent->setX(xPos);
                    }

                    if (collision[1]) {
                        posComponent->setY(yPos);
                    }

                    colComponent->update();
                }
            }

        }
    }
}


