#pragma once
#include "GameObject.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <StaticObject.hpp>


class Map {
    public:
        Map();
        ~Map();
        int loadBlocksFromFile(const std::string &fileName);
        void spawnBlocks();

        int loadObjectsFromJSONFile(const std::string& fileName);

        void render();

    private:
        std::vector<std::vector<int>> blockGrid;
        std::vector<std::vector<std::shared_ptr<StaticObject>>> blocks;

        std::vector<std::shared_ptr<StaticObject>> props;
};

