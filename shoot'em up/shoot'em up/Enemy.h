#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <cmath>
#include "Projectile.h"

class Player;

class Enemy {
public:
    float x, y;
    SDL_FRect rect;
    std::vector<Projectile> projectiles;
    float moveTimer;
    float shotTimer;

    Enemy(float px, float py);
    virtual ~Enemy() = default;

    virtual void update(float deltaTime, Player& player) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual bool checkCollision(const SDL_FRect& other);
    virtual int getType() const = 0;
};

class BasicEnemy : public Enemy {
public:
    BasicEnemy(float px, float py);

    void update(float deltaTime, Player& player) override;
    void render(SDL_Renderer* renderer) override;
    int getType() const override;
};

class ZigzagEnemy : public Enemy {
public:
    ZigzagEnemy(float px, float py);

    void update(float deltaTime, Player& player) override;
    void render(SDL_Renderer* renderer) override;
    int getType() const override;
};

class ShulkerEnemy : public Enemy {
private:
    float invulnerabilityTimer;  // Pour suivre le temps
    bool isInvulnerable;         // État actuel
public:
    ShulkerEnemy(float px, float py);

    void update(float deltaTime, Player& player) override;
    void render(SDL_Renderer* renderer) override;
    bool checkCollision(const SDL_FRect& other) override;  // Override pour gérer l'invulnérabilité
    int getType() const override;
};

class DragonEnemy : public Enemy {

public:
    DragonEnemy(float px, float py);

    void update(float deltaTime, Player& player) override;
    void render(SDL_Renderer* renderer) override;
    int getType() const override;
};

std::unique_ptr<Enemy> createEnemy(int type, float x, float y);