#pragma once
#include "GameObject.hpp"
#include <string>
#include <vector>
#include <StaticObject.hpp>


class Map {
    public:
        Map();
        ~Map();
        int loadFromFile(const std::string &fileName);
        void spawnBlocks();
        void render();

    private:
        std::vector<std::vector<int>> map;
        std::vector<std::vector<std::shared_ptr<StaticObject>>> blocks;
};

