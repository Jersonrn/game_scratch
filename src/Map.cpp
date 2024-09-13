#include "Game.hpp"
#include "GameObject.hpp"
#include "StaticObject.hpp"
#include "Texture.hpp"
#include <Map.hpp>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>


Map::Map() {}

Map::~Map() {
    /* std::cout << "Cleanning map" << std::endl; */
    /* for (size_t y = 0; y < this->map.size(); ++y) { */
    /*     for (size_t x = 0; x < this->map[y].size(); ++x) { */
    /*         this->blocks[y][x]; */
    /*     } */
    /* } */
}

int Map::loadFromFile(const std::string &fileName) {
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

        this->map.push_back(row);
    }

    file.close();
    this->spawnBlocks();
    return 0;
}

void Map::spawnBlocks() {
    this->blocks.clear();

    for (size_t y = 0; y < this->map.size(); ++y) {
        std::vector<std::shared_ptr<StaticObject>> row;

        for (size_t x = 0; x < this->map[y].size(); ++x) {
            int tileID = this->map[y][x];

            // args
            float xPos = x * 64;
            float yPos = y * 64;
            float xScale = 1;
            float yScale = 1;
            float srcRectX;
            float srcRectY;
            float srcRectW = 64;
            float srcRectH = 64;

            switch (tileID) {
                case 0:
                    break;
                case 1:
                    srcRectX = 384;
                    srcRectY = 0;
                    auto block = std::make_shared<StaticObject>("res/tiles.webp", xPos, yPos, xScale, yScale, srcRectX, srcRectY, srcRectW, srcRectH);
                    row.push_back(block);
            }
        }

        this->blocks.push_back(row);
    }
}

void Map::render(){
    for (size_t y = 0; y < this->blocks.size(); ++y) {
        for (size_t x = 0 ; x < this->blocks[y].size(); ++x) {
            this->blocks[y][x]->render();
        }
    }
}
