#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include "Button.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"

struct ScriptCommand {
    float time;
    std::string command;
    std::vector<std::string> params;
};

class Level2 {
public:
    Level2();
    void handleEvent(const SDL_Event& event, bool& shouldSwitchToMenu);
    void update(float deltaTime);
    void draw(SDL_Renderer* renderer);
    bool isCompleted() const;
    bool isFailed() const;

private:
    Player player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<Projectile> allProjectiles;
    std::vector<ScriptCommand> script;
    size_t currentCommand;
    Uint64 levelStartTime;
    bool levelCompleted;
    bool levelFailed;
    Button button;

    std::vector<ScriptCommand> loadScript(const std::string& filename);
    void executeCommand(const ScriptCommand& cmd);
    void handleCollisions();
};