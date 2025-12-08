#include "LevelLoader.h"
#include <fstream>
#include <iostream>

bool LevelLoader::load(const std::string& path,
    std::vector<std::string>& outMap,
    int& outRows,
    int& outCols)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Cannot open level file: " << path << "\n";
        return false;
    }

    outMap.clear();
    std::string line;

    while (std::getline(file, line)) {
        outMap.push_back(line);
    }

    outRows = (int)outMap.size();
    outCols = outRows > 0 ? (int)outMap[0].size() : 0;

    return true;
}
