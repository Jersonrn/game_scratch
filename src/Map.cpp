#include "Game.hpp"
#include "StaticObject.hpp"
#include <Map.hpp>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


Map::Map() {}

Map::~Map() {}

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
    return 0;
}

void Map::render(){
    for (size_t y = 0 ; y < this->map.size(); ++y) {
        for (size_t x = 0 ; x < this->map[y].size(); ++x) {
            int tileID = this->map[y][x];

            //args
            std::string pathFile = "res/tiles.webp";
            float xPos = x * 64;
            float yPos = y * 64;
            float xScale = 1;
            float yScale = 1;

            switch (tileID) {
                case 0:
                    break;
                case 1:
                    float srcRectX = 384;
                    float srcRectY = 0;
                    float srcRectW = 64;
                    float srcRectH = 64;

                    StaticObject block(pathFile, xPos, yPos, xScale, yScale, srcRectX, srcRectY, srcRectW, srcRectH);
                    block.render();
            }
        }
    }
    std::cout << "****************************************" << std::endl;
}
