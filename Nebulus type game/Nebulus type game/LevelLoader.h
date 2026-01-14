#pragma once
#include <string>
#include <vector>

// Structure pour les commandes de script
struct ScriptCommand {
    float time;
    std::string command;
    std::vector<std::string> params;
};

class LevelLoader {
public:
    // Charge l'ordre des niveaux depuis Levels_order.txt
    static bool loadLevelsOrder(const std::string& path, std::vector<std::string>& outLevels);

    // Charge un script de niveau (commandes temporisées)
    static bool loadLevelScript(const std::string& path, std::vector<ScriptCommand>& outScript);
};