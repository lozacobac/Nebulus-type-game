#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "Projectile.h"

class Player {
public:
    float x, y;
    int lives;
    SDL_FRect rect;
    std::vector<Projectile> projectiles;

    Player();
    void update(const bool* keys, float deltaTime);  // Changé Uint8* en bool*
    void render(SDL_Renderer* renderer);
    bool checkCollision(const SDL_FRect& other);
};