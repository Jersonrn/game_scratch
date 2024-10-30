#include "Component.hpp"
#include "Entity.hpp"
#include <Enemy.hpp>


Enemy::Enemy(
        std::shared_ptr<std::unordered_map<
            ComponentBitset,
            std::vector<std::shared_ptr<Entity>>,
            BitsetHash
        >> ptrArchetypes
        ) : Entity(ptrArchetypes) {
}

int Enemy::initialize() {
    this->addComponent<Sprite>("res/enemy.webp", 0, 0, 128, 128);
    this->addComponent<Velocity>(0., 0.);
    this->addComponent<Position>(500., 302.);
    this->addComponent<Scale>(1., 1.);
    this->addComponent<Collision>(500, 128, 302, 128);
    this->addComponent<Animator>();
    Animator* animator = this->getComponent<Animator>();
    animator->loadAnimationFromJSON("res/anim/walkEnemy.json");
    animator->setAnimation("WALK");
    this->addComponent<Render>();

    return 0;
}

Enemy::~Enemy() {}
