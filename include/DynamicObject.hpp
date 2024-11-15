#pragma once
#include "GameObject.hpp"


class DynamicObject : public GameObject{
    public:
        DynamicObject(
                const std::string &pathFile,
                float xPos = 0, float yPos = 0,
                float xScale_ = 1, float yScale_ = 1,
                int srcRectX = 0, int srcRectY = 0, int srcRectW = -1, int srcRectH = -1
                );
        virtual ~DynamicObject();

        void update(float deltaTime) override;

        void move(float x, float y) override;

        void setVelocity(float x, float y);

        void setDirection(float x, float y);

    private:
        float xVelocity;
        float yVelocity;
        float xDirection;
        float yDirection;
};
