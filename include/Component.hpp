#pragma once
#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

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

class Animator: public Component {
    private:
        float currentFrame;
        std::string currentAnimation;

    public:
        std::unordered_map<std::string, std::vector<std::vector<int>>> animations;

        Animator(std::shared_ptr<Entity> entity);
        virtual ~Animator();

        void addAnimation(std::string &name, std::vector<std::vector<int>> &&frames);
        void update(float deltaTime);
        void setAnimation(std::string anim);
        int getCurrentFrame();
        void nextFrame();
        void updateFrame(float deltaTime);
        int loadAnimationFromJSON(std::string path);
};

class Render: public Component {
    public:
        Render(std::shared_ptr<Entity> entity);
        virtual ~Render();
};
