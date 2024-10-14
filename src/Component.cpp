#include <Component.hpp>


Component::Component() {}

Component::~Component() {}


//VELOCITY
Velocity::Velocity(float x, float y)
    : x(x), y(y) {};

Velocity::~Velocity() {};



//POSITION
Position::Position(float x, float y)
    : x(x), y(y) {};

Position::~Position() {};


//HEALTH


//RENDER
Render::Render() {};
Render::~Render() {};
