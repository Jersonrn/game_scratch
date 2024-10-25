#include <Entity.hpp>
#include <Component.hpp>
#include <SDL2/SDL_rect.h>
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <json.hpp>
#include <fstream>
using json = nlohmann::json;


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
    : Component(entity) {
        this->entity->texture->setXPosition(x);
        this->entity->texture->setYPosition(y);
    };

Position::~Position() {};

float Position::x() { return this->entity->texture->getXPosition(); }
float Position::y() { return this->entity->texture->getYPosition(); }

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
Collision::Collision(std::shared_ptr<Entity> entity,int x, int w, int y, int h)
    : Component(entity) {
        this->colRect = { x, y, w, h };
    };

Collision::~Collision() {};

void Collision::update() {
    int x = this->entity->texture->getXPosition();
    int y = this->entity->texture->getYPosition();
    int w = this->entity->texture->getXScale();
    int h = this->entity->texture->getYScale();

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
        float srcRectW = this->animations[this->currentAnimation][this->getCurrentFrame()][1];
        this->entity->texture->setXCrop(srcRectX, srcRectW);

        float srcRectY = this->animations[this->currentAnimation][this->getCurrentFrame()][2];
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

            std::cerr << "The "<< anim << " animation does not exist in animations, setting to " << firstKey;
            this->currentAnimation = firstKey;
        } else {
            this->currentAnimation = anim;
        }
    } else {
        std::cerr << "Animations is void!";
    }
}

void Animator::updateFrame(float deltaTime) {
    this->currentFrame += static_cast<float>(this->animations[this->currentAnimation].size()) * deltaTime;

    if (this->currentFrame >= this->animations[this->currentAnimation].size()) {
        this->currentFrame = 0;
    }
}

void Animator::nextFrame() {
    if (this->currentFrame >= this->animations[this->currentAnimation].size()) {
        this->currentFrame = 0;
    } else {
        this->currentFrame++;
    }
}

int Animator::loadAnimationFromJSON(std::string path) {
    std::ifstream inputFile(path);
    if (!inputFile.is_open()) {
        std::cerr << "Eror opening " << path << "file." << std::endl;
        return 1;
    }

    // Parse JSON file
    nlohmann::json json;
    inputFile >> json;
    inputFile.close();

    for (const auto& row : json["WALK"]) {
        std::vector<int> innerVec = row.get<std::vector<int>>();
        this->animations["WALK"].push_back(innerVec);
    }

    return 0;
};


//RENDER
Render::Render(std::shared_ptr<Entity> entity)
    : Component(entity) { };
Render::~Render() {};
