#include "GameObject.hpp"
#include <StaticObject.hpp>


StaticObject::StaticObject(
        const std::string &pathFile,
        float xPos, float yPos,
        float xScale_, float yScale_,
        int srcRectX, int srcRectY, int srcRectW, int srcRectH
        ) : GameObject(pathFile, xPos, yPos, xScale_, yScale_, srcRectX, srcRectY, srcRectW, srcRectH){
}

void StaticObject::move(float x, float y) {}
