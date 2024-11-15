#include "Utils.hpp"
#include <Entity.hpp>
#include <Component.hpp>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <array>
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <json.hpp>
#include <fstream>


Component::Component(std::shared_ptr<Entity> entity)
    : entity(entity) {}

Component::~Component() {}


//VELOCITY
Velocity::Velocity(std::shared_ptr<Entity> entity, float x, float y)
    : Component(entity), x(x), y(y) {
    };

Velocity::~Velocity() {};


//POSITION
Position::Position(std::shared_ptr<Entity> entity,float x, float y)
    : Component(entity), x(x), y(y) {
        this->entity->texture->setXPosition(this->x);
        this->entity->texture->setYPosition(this->y);
    };

Position::~Position() {};

float Position::getX() { return this->x; }
float Position::getY() { return this->y; }

void Position::setX(float x) {
    this->x = x;
    this->entity->texture->setXPosition(this->x);
};
void Position::setY(float y) {
    this->y = y;
    this->entity->texture->setYPosition(this->y);
};

void Position::update(float x, float y) {
    this->entity->texture->setXPosition(x);
    this->entity->texture->setYPosition(y);
};


//SCALE
Scale::Scale(std::shared_ptr<Entity> entity,float x, float y)
    : Component(entity), x(x), y(y) {
        this->entity->texture->setXScale(x);
        this->entity->texture->setYScale(y);
    };

Scale::~Scale() {};


//COLLISION
Collision::Collision(std::shared_ptr<Entity> entity,int x, int y, int w,int h)
    : Component(entity), xOffset(x), yOffset(y), width(w), height(h) {
        this->colRect = { this->xOffset, this->yOffset, this->width, this->height };
    };

Collision::~Collision() {};

void Collision::update() {
    int x = this->entity->texture->getXPosition() + this->xOffset;
    int y = this->entity->texture->getYPosition() + this->yOffset;
    int w = this->width;
    int h = this->height;

    this->colRect = {x, y, w, h};
};

bool Collision::hasCollision(SDL_Rect *B) {
    return SDL_HasIntersection(this->getRect(), B);
};

SDL_Rect* Collision::getRect() {
    return &this->colRect;
};


//SPRITE
Sprite::Sprite(
        std::shared_ptr<Entity> entity,
        const std::string &pathFile,
        int srcRectX = 0, int srcRectY = 0, int srcRectW = -1, int srcRectH = -1
    ) : Component(entity){
        this->entity->texture->load_from_file(
                pathFile,
                srcRectX, srcRectY, srcRectW, srcRectH
        );
    };

Sprite::~Sprite() {};


//INPUTKEY
InputKey::InputKey(std::shared_ptr<Entity> entity)
    : Component(entity) { };

InputKey::~InputKey() {};

void InputKey::update(const SDL_Event& event) {
    this->entity->handleInputEvents(event);
};


//ANIMATOR
Animator::Animator(std::shared_ptr<Entity> entity)
    : Component(entity) { };

Animator::~Animator() {};

void Animator::addAnimation(std::string &name, std::vector<std::vector<int>> &&frames) {
    this->animations[name] = frames;
};

void Animator::update(float deltaTime) {
    if (!this->animations.empty()) {
        this->updateFrame(deltaTime);

        float srcRectX = this->animations[this->currentAnimation][this->getCurrentFrame()][0];
        float srcRectW = this->animations[this->currentAnimation][this->getCurrentFrame()][2];
        this->entity->texture->setXCrop(srcRectX, srcRectW);

        float srcRectY = this->animations[this->currentAnimation][this->getCurrentFrame()][1];
        float srcRectH = this->animations[this->currentAnimation][this->getCurrentFrame()][3];
        this->entity->texture->setYCrop(srcRectY, srcRectH);
    }
}

int Animator::getCurrentFrame() {
    return this->currentFrame;
}

void Animator::setAnimation(std::string anim) {
    if (!this->animations.empty()) {
        if (this->animations.find(anim) == this->animations.end()) {
            auto iterator = this->animations.begin();
            std::string firstKey = iterator->first;

            std::cerr << "The "<< anim << " animation does not exist in animations, setting to " << firstKey << std::endl;
            this->currentAnimation = firstKey;
        } else {
            this->currentAnimation = anim;
        }
    } else {
        std::cerr << "Animations is void!" << std::endl;
    }
}

void Animator::updateFrame(float deltaTime) {
    this->currentFrame += static_cast<float>(this->animations[this->currentAnimation].size()) * deltaTime;

    if (this->currentFrame >= this->animations[this->currentAnimation].size()) {
        this->currentFrame = 0;
    }
}

// deprecated
void Animator::nextFrame() {
    if (this->currentFrame >= this->animations[this->currentAnimation].size()) {
        this->currentFrame = 0;
    } else {
        this->currentFrame++;
    }
}

int Animator::loadAnimationFromJSON(const std::string& path, const std::string& name) {
    nlohmann::json json = loadJSONFile(path);

    for (const auto& row : json[name]) {
        std::vector<int> innerVec = row.get<std::vector<int>>();
        this->animations[name].push_back(innerVec);
    }

    return 0;
};

int Animator::loadAnimationsFromJSON(const std::string& path) {
    nlohmann::json json = loadJSONFile(path);

    for (const auto& item: json.items()) {
        this->loadAnimationFromJSON(path, item.key());
        /* for (const auto& row : json[item.key()]) { */
        /*     std::vector<int> innerVec = row.get<std::vector<int>>(); */
        /*     this->animations[item.key()].push_back(innerVec); */
        /* } */
    }

    return 0;
};

//RENDER
Render::Render(std::shared_ptr<Entity> entity)
    : Component(entity) { };
Render::~Render() {};
