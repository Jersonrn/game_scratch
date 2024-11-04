#include <Player.hpp>
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
    this->addComponent<Velocity>(0., 0.);
    this->addComponent<Position>(200., 525.);
    this->addComponent<Scale>(1., 1.);
    this->addComponent<Collision>(100, 200, 64, 64);
    this->addComponent<InputKey>();
    this->addComponent<Animator>();
    Animator* animator = this->getComponent<Animator>();
    animator->loadAnimationsFromJSON("res/anim/animationsPlayer.json");
    animator->setAnimation("RUN");
    this->addComponent<Render>();

    return 0;
}

Player::~Player() {}

void Player::handleInputEvents(const SDL_KeyboardEvent& keyEvent) {
    /* https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlkey.html */
    if (keyEvent.keysym.sym == SDLK_LEFT) {
        this->getComponent<Velocity>()->x = -100.;
        std::cout << "vel: " << this->getComponent<Velocity>()->x << std::endl;
    } else if (keyEvent.keysym.sym == SDLK_RIGHT) {
        this->getComponent<Velocity>()->x = 100.;
        std::cout << "vel: " << this->getComponent<Velocity>()->x << std::endl;
    } else if (keyEvent.keysym.sym == SDLK_UP) {
        this->getComponent<Velocity>()->y = -100.;
        std::cout << "vel: " << this->getComponent<Velocity>()->y << std::endl;
    } else if (keyEvent.keysym.sym == SDLK_DOWN) {
        this->getComponent<Velocity>()->y =100.;
        std::cout << "vel: " << this->getComponent<Velocity>()->y << std::endl;
    }
}
