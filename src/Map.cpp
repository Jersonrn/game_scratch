#include "Game.hpp"
#include "GameObject.hpp"
#include "StaticObject.hpp"
#include "Texture.hpp"
#include "Utils.hpp"
#include <Map.hpp>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <json.hpp>


Map::Map() {}

Map::~Map() {
    /* std::cout << "Cleanning map" << std::endl; */
    /* for (size_t y = 0; y < this->map.size(); ++y) { */
    /*     for (size_t x = 0; x < this->map[y].size(); ++x) { */
    /*         this->blocks[y][x]; */
    /*     } */
    /* } */
}

int Map::loadBlocksFromFile(const std::string &fileName) {
    std::ifstream file(fileName);

    if (!file) {
        std::cerr << "Error opening file map" << std::endl;
        return -1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;

        for (char c : line) {
            if (std::isdigit(c)) {
                int digit = std::stoi(&c);
                row.push_back(digit);
            }
        }

        this->blockGrid.push_back(row);
    }

    file.close();
    this->spawnBlocks();
    return 0;
}

void Map::spawnBlocks() {
    this->blocks.clear();

    for (size_t y = 0; y < this->blockGrid.size(); ++y) {
        std::vector<std::shared_ptr<StaticObject>> row;

        for (size_t x = 0; x < this->blockGrid[y].size(); ++x) {
            int tileID = this->blockGrid[y][x];

            // args
            float xPos = x * 64;
            float yPos = y * 64;
            float xScale = 64;
            float yScale = 64;
            float srcRectX;
            float srcRectY;
            float srcRectW = 64;
            float srcRectH = 64;
            std::shared_ptr<StaticObject> block;

            switch (tileID) {
                case 0:
                    break;
                case 1:
                    srcRectX = 384;
                    srcRectY = 0;
                    block = std::make_shared<StaticObject>("res/tiles.webp", xPos, yPos, xScale, yScale, srcRectX, srcRectY, srcRectW, srcRectH);
                    row.push_back(block);
                    break;
                case 2:
                    srcRectX = 0;
                    srcRectY = 64;
                    block = std::make_shared<StaticObject>("res/tiles.webp", xPos, yPos, xScale, yScale, srcRectX, srcRectY, srcRectW, srcRectH);
                    row.push_back(block);
                    break;
                case 3:
                    srcRectX = 0;
                    srcRectY = 0;
                    block = std::make_shared<StaticObject>("res/tiles.webp", xPos, yPos, xScale, yScale, srcRectX, srcRectY, srcRectW, srcRectH);
                    row.push_back(block);
                    break;
                case 4:
                    srcRectX = 128;
                    srcRectY = 0;
                    block = std::make_shared<StaticObject>("res/tiles.webp", xPos, yPos, xScale, yScale, srcRectX, srcRectY, srcRectW, srcRectH);
                    row.push_back(block);
                    break;
                case 5:
                    srcRectX = 192;
                    srcRectY = 0;
                    block = std::make_shared<StaticObject>("res/tiles.webp", xPos, yPos, xScale, yScale, srcRectX, srcRectY, srcRectW, srcRectH);
                    row.push_back(block);
                    break;
            }
        }

        this->blocks.push_back(row);
    }
}

int Map::loadObjectsFromJSONFile(const std::string& fileName, std::vector<std::shared_ptr<StaticObject>>& container) {
    nlohmann::json json = loadJSONFile(fileName);

    for (const auto& obj : json.items()) {
        for (size_t i = 0; i < obj.value()["info"].size(); ++i) {
            std::shared_ptr<StaticObject> objStatic = std::make_shared<StaticObject>(
                    obj.value()["path"],
                    //dst
                    obj.value()["info"][i][0][0], obj.value()["info"][i][0][1],
                    obj.value()["info"][i][0][2], obj.value()["info"][i][0][3],
                    //src
                    obj.value()["info"][i][1][0], obj.value()["info"][i][1][1],
                    obj.value()["info"][i][1][2], obj.value()["info"][i][1][3]
            );
            container.push_back(objStatic);
        }
    }
    return 0;
}
int Map::loadCollisionFromJSONFile(
        const std::string& fileName,
        std::shared_ptr<std::unordered_map<
            ComponentBitset,
            std::vector<std::shared_ptr<Entity>>,
            BitsetHash
        >> ptrArchetypes
) {
    nlohmann::json json = loadJSONFile(fileName);

    for (const auto& obj : json.items()) {
        for (size_t i = 0; i < obj.value()["info"].size(); ++i) {
            std::shared_ptr<Entity> colEntity = std::make_shared<Entity>(ptrArchetypes);
            /* colEntity->addComponent<Position>(100, 100); */
            /* colEntity->addComponent<Scale>(1., 1.); */
            colEntity->addComponent<Collision>(
                    obj.value()["info"][i][0], obj.value()["info"][i][1],
                    obj.value()["info"][i][2], obj.value()["info"][i][3]
            );
            this->colBlocks.push_back(colEntity);
        }
    }

    return 0;
}

void Map::render(){
    for (size_t i = 0; i < this->environment.size(); ++i) {
        this->environment[i]->render();
    }

    for (size_t i = 0; i < this->props.size(); ++i) {
        this->props[i]->render();
    }

    for (size_t y = 0; y < this->blocks.size(); ++y) {
        for (size_t x = 0 ; x < this->blocks[y].size(); ++x) {
            this->blocks[y][x]->render();
        }
    }
}

