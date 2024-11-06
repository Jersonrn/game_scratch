#include "Utils.hpp"
#include <cstddef>
#include "json.hpp"
#include <fstream>
#include <iostream>

std::size_t lastComponentID = 0;

nlohmann::json loadJSONFile(const std::string& path) {
    std::ifstream inputFile(path);
    if (!inputFile.is_open()) {
        std::cerr << "Eror opening " << path << " file." << std::endl;
        return nlohmann::json();
    }

    nlohmann::json json;
    try {
        // Parse JSON file
        inputFile >> json;
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "Parse Error: " << e.what() << std::endl;
        return nlohmann::json();
    }
    inputFile.close();

    return json;
}
