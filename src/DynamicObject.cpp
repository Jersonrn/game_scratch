#include "GameObject.hpp"
#include <DynamicObject.hpp>


DynamicObject::DynamicObject(
        const std::string &pathFile,
        float xPos, float yPos,
        float xScale_, float yScale_,
        int srcRectX, int srcRectY, int srcRectW, int srcRectH 
        ): GameObject(pathFile, xPos, yPos, xScale_, yScale_, srcRectX, srcRectY, srcRectW, srcRectH) {}

DynamicObject::~DynamicObject() {}
