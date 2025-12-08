#pragma once
#include <vector>
#include <string>

class LevelLoader {
public:
    bool load(const std::string& path,
        std::vector<std::string>& outMap,
        int& outRows,
        int& outCols);
};
