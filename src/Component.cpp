#include <Entity.hpp>
#include <Component.hpp>
#include <cstddef>
#include <memory>
#include <string>


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
        this->entity->texture->setXPosition(x);
        this->entity->texture->setYPosition(y);
    };

Position::~Position() {};


//SCALE
Scale::Scale(std::shared_ptr<Entity> entity,float x, float y)
    : Component(entity), x(x), y(y) {
        this->entity->texture->setXScale(x);
        this->entity->texture->setYScale(y);
    };

Scale::~Scale() {};


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

//RENDER
Render::Render(std::shared_ptr<Entity> entity)
    : Component(entity) { };
Render::~Render() {};
