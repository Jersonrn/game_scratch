#pragma once
#include <string>
#include <vector>
#include <StaticObject.hpp>


class Map {
    public:
        Map();
        ~Map();
        int loadFromFile(const std::string &fileName);
        void render();

    private:
        std::vector<std::vector<int>> map;
};

