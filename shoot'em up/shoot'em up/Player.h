#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "Projectile.h"

class Player {
private:
    int screenWidth;
    int screenHeight;
public:
    float x, y;
    int lives;
    SDL_FRect rect;
    std::vector<Projectile> projectiles;
    float invicibilityTimer; //Timer pour invinciblitlité

    Player();
    Player(int width, int height);
    void update(const bool* keys, float deltaTime);  // Changé Uint8* en bool*
    void render(SDL_Renderer* renderer);
    bool checkCollision(const SDL_FRect& other);
    bool isInvincible() const { return invicibilityTimer > 0; } //Métode pour vérifier l'invincibilité
    void setScreenBounds(int width, int height);
};