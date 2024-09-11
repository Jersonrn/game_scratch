#pragma once
#include <string>
#include <vector>


class Map {
    public:
        Map();
        ~Map();
        int loadFromFile(const std::string &fileName);

    private:
        std::vector<std::vector<int>> map;
};

