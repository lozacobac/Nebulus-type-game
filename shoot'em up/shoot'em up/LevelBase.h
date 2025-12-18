#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Button.h"
#include "LevelLoader.h"
#include <SDL3_ttf/SDL_ttf.h>

class LevelBase {
protected:
    TTF_Font* font;
    Player player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<Projectile> allProjectiles;
    std::vector<ScriptCommand> script;
    Button menuButton;
    SDL_Texture* scoreTexture;
    SDL_FRect scoreRect;
    size_t currentCommand;
    Uint64 levelStartTime;
    bool levelCompleted;
    bool levelFailed;
    int score;
    int screenWidth;
    int screenHeight;

    virtual void executeCommand(const ScriptCommand& cmd);
    void handleCollisions();

public:
    LevelBase() = default;
    LevelBase(TTF_Font* font, int width, int height);
    virtual ~LevelBase() = default;

    bool loadFromFile(const std::string& scriptPath, SDL_Renderer* renderer);

    // Santé des boss (utilisés selon le niveau)
    int DragonHealth;   // Pour le Dragon (type 9)
    int WardenHealth;   // Pour le Warden (type 12)

    virtual void handleEvent(const SDL_Event& event, bool& shouldSwitchToMenu);
    virtual void update(float deltaTime);
    virtual void draw(SDL_Renderer* renderer);

    bool isCompleted() const;
    bool isFailed() const;
    int getScore() const;
};