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
    float shotTimer; // cooldown pour le projectile
public:
    float x, y;
    SDL_FRect rect;
    std::vector<Projectile> projectiles;
    float moveTimer;

    Enemy(float px, float py, int sw, int sh);
    virtual ~Enemy() = default;

    virtual void update(float deltaTime, Player& player) = 0; // IA de l'ennemi
    virtual void render(SDL_Renderer* renderer) = 0; // Dessiner l'ennemi
    virtual bool checkCollision(const SDL_FRect& other); // Permet de savoir si oui ou non les dégats sont acceptés
    virtual int getType() const = 0; // ID de l'ennemi
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

class Drowned : public Enemy {
public:
    Drowned(float px, float py, int sw, int sh);

    void update(float deltaTime, Player& player) override;
    void render(SDL_Renderer* renderer) override;
    int getType()const override;
};

class Guardian : public Enemy {
public:
    Guardian(float px, float py, int sw, int sh);

    void update(float deltaTime, Player& player) override;
    void render(SDL_Renderer* renderer) override;
    int getType()const override;

private:
    // Plusieurs états pour l'ennemi
    enum Phase { BURST, PAUSE };
    Phase currentPhase = BURST;
    float phaseTimer = 0.0f;
    float shotTimer = 0.0f;
};

class Elder_Guardian : public Enemy {
public:
    Elder_Guardian(float px, float py, int sw, int sh);

    void update(float deltaTime, Player& player) override;
    void render(SDL_Renderer* renderer) override;
    int getType()const override;

private:
    // Plusieurs états pour l'ennemi
    enum Phase { BURST, PAUSE };
    Phase currentPhase = BURST;
    float phaseTimer = 0.0f;
    float shotTimer = 0.0f;
};
class SkeletonEnemy : public Enemy {
public:
    SkeletonEnemy(float px, float py, int sw, int sh);

    void update(float deltaTime, Player& player) override;
    void render(SDL_Renderer* renderer) override;
    int getType() const override;
};

class BlazeEnemy : public Enemy {
public:
    BlazeEnemy(float px, float py, int sw, int sh);

    void update(float deltaTime, Player& player) override;
    void render(SDL_Renderer* renderer) override;
    int getType() const override;
};


class ShulkerEnemy : public Enemy {
private:
    // Est invincible en fonction du temps
    float invulnerabilityTimer;
    bool isInvulnerable;
public:
    ShulkerEnemy(float px, float py, int sw, int sh);

    void update(float deltaTime, Player& player) override;
    void render(SDL_Renderer* renderer) override;
    bool checkCollision(const SDL_FRect& other) override; // Permet de savoir si oui ou non les dégats sont acceptés
    int getType() const override;
};

class DragonBoss : public Enemy {

public:
    DragonBoss(float px, float py, int sw, int sh);
    void update(float deltaTime, Player& player) override;
    void render(SDL_Renderer* renderer) override;
    int getType() const override;
};

class EndermanEnemy : public Enemy {

public:
    EndermanEnemy(float px, float py, int sw, int sh);
    void update(float deltaTime, Player& player) override;
    void render(SDL_Renderer* renderer) override;
    int getType() const override;
};

std::unique_ptr<Enemy> createEnemy(int type, float x, float y, int screenWidth, int screenHeight);