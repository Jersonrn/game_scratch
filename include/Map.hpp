#pragma once
#include "Entity.hpp"
#include "GameObject.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <StaticObject.hpp>


class Map {
    public:
        std::vector<std::shared_ptr<StaticObject>> props;
        std::vector<std::shared_ptr<StaticObject>> environment;

        Map();
        ~Map();
        int loadBlocksFromFile(const std::string &fileName);
        void spawnBlocks();

        int loadObjectsFromJSONFile(const std::string& fileName, std::vector<std::shared_ptr<StaticObject>>& container);

        int loadCollisionFromJSONFile(
                const std::string& fileName,
                std::shared_ptr<std::unordered_map<
                    ComponentBitset,
                    std::vector<std::shared_ptr<Entity>>,
                    BitsetHash
                >> ptrArchetypes
        );

        void render();

    private:
        std::vector<std::vector<int>> blockGrid;
        std::vector<std::vector<std::shared_ptr<StaticObject>>> blocks;

        std::vector<std::shared_ptr<Entity>> colBlocks;

};

