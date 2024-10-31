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
    ComponentBitset posBitSet = getComponentBitset<Position>() | getComponentBitset<Velocity>();

    for (const auto &e : (*this->ptrArchetypes)[posBitSet]) {
        Position* posComponent = e->getComponent<Position>();
        float xPos = posComponent->getX();
        float yPos = posComponent->getY();

        Velocity* velComponent = e->getComponent<Velocity>();
        float newXpos = xPos + (velComponent->x * deltaTime);
        float newYpos = yPos + (velComponent->y * deltaTime);

        if (e->hasComponent<Collision>()) {
            Collision* colComponent = e->getComponent<Collision>();
            ComponentBitset colBitset = getComponentBitset<Collision>();

            posComponent->setX(newXpos);
            colComponent->update();
            for (const auto& colEntity : (*this->ptrArchetypes)[colBitset]) {
                if (colEntity->getID() != e->getID()) {
                    SDL_Rect* B = colEntity->getComponent<Collision>()->getRect();
                    if (colComponent->hasCollision(B)) {
                        posComponent->setX(xPos);
                    }
                }
            }

            posComponent->setY(newYpos);
            colComponent->update();
            for (const auto& colEntity : (*this->ptrArchetypes)[colBitset]) {
                if (colEntity->getID() != e->getID()) {
                    SDL_Rect* B = colEntity->getComponent<Collision>()->getRect();
                    if (colComponent->hasCollision(B)) {
                        posComponent->setY(yPos);
                    }
                }
            }

            colComponent->update();

        } else {
            e->updatePosition(deltaTime);
        }
    }
}


