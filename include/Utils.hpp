#pragma once
#include <bitset>
#include <cstddef>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#ifndef UTILS_H
#define UTILS_H


class Component;

const int MAX_FPS = 64;

static constexpr float PIXELS_PER_METER = 32.f;
static constexpr float GRAVITY_ACCELERATION = 9.8f;


static const int MAXCOMPONENTS = 8;
using ComponentBitset = std::bitset<MAXCOMPONENTS>;

/* template<std::size_t N> */
/* using ComponentBitset = std::bitset<N>; */


struct BitsetHash {
    std::size_t operator()(const ComponentBitset &b) const {
        return std::hash<std::string>()(b.to_string());
    }
};


extern std::size_t lastComponentID;

template <class T>
typename std::enable_if<std::is_base_of<Component, T>::value, std::size_t>::type
getComponentID() {
    static std::size_t typeID = lastComponentID++;
    return typeID;
};

template <class T>
typename std::enable_if<std::is_base_of<Component, T>::value, ComponentBitset>::type
getComponentBitset() {
    ComponentBitset bitset;
    std::size_t ID = getComponentID<T>();

    bitset[ID] = true;

    return bitset;
};

#endif

