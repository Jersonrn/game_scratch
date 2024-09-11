#include <Map.hpp>
#include <cctype>
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

