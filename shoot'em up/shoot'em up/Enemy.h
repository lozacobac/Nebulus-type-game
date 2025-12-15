#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <cmath>
#include "Projectile.h"

class Player;

class Enemy {
protected:
    int screenWidth;
    int screenHeight;
public:
    float x, y;
    SDL_FRect rect;
    std::vector<Projectile> projectiles;
    float moveTimer;
    float shotTimer;

    Enemy(float px, float py, int sw, int sh);
    virtual ~Enemy() = default;

    virtual void update(float deltaTime, Player& player) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual bool checkCollision(const SDL_FRect& other);
    virtual int getType() const = 0;
};

class BasicEnemy : public Enemy {
public:
    BasicEnemy(float px, float py, int sw, int sh);

    void update(float deltaTime, Player& player) override;
    void render(SDL_Renderer* renderer) override;
    int getType() const override;
};

class ZigzagEnemy : public Enemy {
public:
    ZigzagEnemy(float px, float py, int sw, int sh);

    void update(float deltaTime, Player& player) override;
    void render(SDL_Renderer* renderer) override;
    int getType() const override;
};

class ShulkerEnemy : public Enemy {
private:
    float invulnerabilityTimer;
    bool isInvulnerable;
public:
    ShulkerEnemy(float px, float py, int sw, int sh);

    void update(float deltaTime, Player& player) override;
    void render(SDL_Renderer* renderer) override;
    bool checkCollision(const SDL_FRect& other) override;
    int getType() const override;
};

class DragonEnemy : public Enemy {

public:
    DragonEnemy(float px, float py, int sw, int sh);
    void update(float deltaTime, Player& player) override;
    void render(SDL_Renderer* renderer) override;
    int getType() const override;
};

class Enderman : public Enemy {

public:
    Enderman(float px, float py, int sw, int sh);
    void update(float deltaTime, Player& player) override;
    void render(SDL_Renderer* renderer) override;
    int getType() const override;
};

std::unique_ptr<Enemy> createEnemy(int type, float x, float y, int screenWidth, int screenHeightj);