#pragma once
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <array>
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
        Position(std::shared_ptr<Entity> entity, float x, float y);
        virtual ~Position();

        float getX();
        float getY();

        void setX(float x);
        void setY(float y);

        void update(float x, float y);
};

class Scale: public Component {
    public:
        float x;
        float y;

        Scale(std::shared_ptr<Entity> entity, float x, float y);
        virtual ~Scale();
};

class Collision: public Component {
    public:
        SDL_Rect colRect;

        Collision(std::shared_ptr<Entity> entity, int x, int w, int y, int h);
        virtual ~Collision();

        void update();

        bool hasCollision(SDL_Rect* B);

        SDL_Rect* getRect();
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

class InputKey: public Component {
    public:
        InputKey(std::shared_ptr<Entity> entity);
        virtual ~InputKey();

        virtual void update(const SDL_Event& event);
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
        int loadAnimationFromJSON(const std::string& path, const std::string& name);
        int loadAnimationsFromJSON(const std::string& path);
};

class Render: public Component {
    public:
        Render(std::shared_ptr<Entity> entity);
        virtual ~Render();
};
