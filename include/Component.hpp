#pragma once
#include <memory>
#include <string>

class Entity;


class Component {
    public:
        std::shared_ptr<Entity> entity;
        Component(std::shared_ptr<Entity> entity);
        virtual ~Component();
};




class Velocity: public Component {
    public:
        float x;
        float y;

        Velocity(std::shared_ptr<Entity> entity, float x, float y);
        virtual ~Velocity();
};

class Position: public Component {
    public:
        float x;
        float y;

        Position(std::shared_ptr<Entity> entity, float x, float y);
        virtual ~Position();
};

class Scale: public Component {
    public:
        float x;
        float y;

        Scale(std::shared_ptr<Entity> entity, float x, float y);
        virtual ~Scale();
};

class Sprite: public Component {
    public:
        Sprite(
            std::shared_ptr<Entity> entity,
            const std::string &pathFile,
            int srcRectX, int srcRectY, int srcRectW, int srcRectH
        );
        virtual ~Sprite();
};

class Render: public Component {
    public:
        Render(std::shared_ptr<Entity> entity);
        virtual ~Render();
};
