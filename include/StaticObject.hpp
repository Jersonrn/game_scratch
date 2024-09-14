#pragma once
#include "GameObject.hpp"


class StaticObject : public GameObject {
    public:
        StaticObject(
                const std::string &pathFile,
                float xPos = 0, float yPos = 0,
                float xScale_ = 1, float yScale_ = 1,
                int srcRectX = 0, int srcRectY = 0, int srcRectW = -1, int srcRectH = -1
                );
        ~StaticObject();

        void move(float x, float y);

    private:
};
