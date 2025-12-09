#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Button.h"
#include "LevelLoader.h"

class LevelBase {
protected:
    Player player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<Projectile> allProjectiles;
    std::vector<ScriptCommand> script;

    Button menuButton;

    size_t currentCommand;
    Uint64 levelStartTime;
    bool levelCompleted;
    bool levelFailed;

    virtual void executeCommand(const ScriptCommand& cmd);
    void handleCollisions();

public:
    LevelBase();
    virtual ~LevelBase() = default;

    bool loadFromFile(const std::string& scriptPath);

    virtual void handleEvent(const SDL_Event& event, bool& shouldSwitchToMenu);
    virtual void update(float deltaTime);
    virtual void draw(SDL_Renderer* renderer);

    bool isCompleted() const;
    bool isFailed() const;
};