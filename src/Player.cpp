#include "Component.hpp"
#include <Player.hpp>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <iostream>


Player::Player(
        std::shared_ptr<std::unordered_map<
            ComponentBitset,
            std::vector<std::shared_ptr<Entity>>,
            BitsetHash
        >> ptrArchetypes
        ) : Entity(ptrArchetypes) {
}

int Player::initialize() {
    this->addComponent<Sprite>("res/robot.webp", 0, 0, 64, 64);
    this->addComponent<Velocity>(0., 100.);
    this->addComponent<Position>(200., 500.);
    this->addComponent<Scale>(1., 1.);
    this->addComponent<Collision>(10, 0, 45, 64);
    this->addComponent<InputKey>();
    this->addComponent<Animator>();
    Animator* animator = this->getComponent<Animator>();
    animator->loadAnimationsFromJSON("res/anim/animationsPlayer.json");
    animator->setAnimation("IDLE");
    this->addComponent<Render>();

    return 0;
}

Player::~Player() {}

void Player::handleInputEvents(const SDL_Event& event) {
    /* https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlkey.html */
    if (event.key.keysym.sym == SDLK_LEFT) {
        if (event.type == SDL_KEYDOWN) {
            this->getComponent<Velocity>()->x = -100.;
            this->getComponent<Animator>()->setAnimation("RUN");
            this->texture->setFlip("HORIZONTAL");

        } else if (event.type == SDL_KEYUP) {
            this->getComponent<Velocity>()->x = 0.;
            this->getComponent<Animator>()->setAnimation("IDLE");
        }

    } else if (event.key.keysym.sym == SDLK_RIGHT) {
        if (event.type == SDL_KEYDOWN) {
            this->getComponent<Velocity>()->x = 100.;
            this->getComponent<Animator>()->setAnimation("RUN");
            this->texture->setFlip("NONE");

        } else if (event.type == SDL_KEYUP) {
            this->getComponent<Velocity>()->x = 0.;
            this->getComponent<Animator>()->setAnimation("IDLE");
        }

    }
}
