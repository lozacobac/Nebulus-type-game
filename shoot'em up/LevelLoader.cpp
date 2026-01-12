#include "LevelLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Charge la liste ordonnée des niveaux à partir d’un fichier texte.
// Retourne 'false' si le fichier ne peut pas être ouvert ou s’il est vide.
bool LevelLoader::loadLevelsOrder(const std::string& path, std::vector<std::string>& outLevels) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Cannot open levels order file: " << path << "\n";
        return false;
    }

    outLevels.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line[0] != '#') { // Ignore les lignes qui commencent avec un #
            outLevels.push_back(line);
        }
    }

    file.close();
    std::cout << "[INFO] Loaded " << outLevels.size() << " levels from " << path << "\n";
    return !outLevels.empty();
}

bool LevelLoader::loadLevelScript(const std::string& path, std::vector<ScriptCommand>& outScript) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Cannot open level script: " << path << "\n";
        return false;
    }

    outScript.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line[0] != '#') {
            ScriptCommand cmd;
            std::istringstream iss(line);
            iss >> cmd.time >> cmd.command;

            std::string param;
            while (iss >> param) {
                cmd.params.push_back(param);
            }

            outScript.push_back(cmd);
        }
    }

    file.close();
    std::cout << "[INFO] Loaded " << outScript.size() << " commands from " << path << "\n";
    return true;
}