#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <string>
#include <iostream>
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
    SDL_Texture* texture;
    SDL_Texture* projectileTexture;
    float width, height;

    Player();
    Player(int width, int height);
    Player(int width, int height,SDL_Renderer* renderer, const char* imagePath);
    ~Player();
    void update(const bool* keys, float deltaTime);  // Changé Uint8* en bool*
    void loadTexture(SDL_Renderer* renderer, const char* imagePath);
    void loadProjectileTexture(SDL_Renderer* renderer, const char* imagePath);
    void render(SDL_Renderer* renderer);
    bool checkCollision(const SDL_FRect& other);
    bool isInvincible() const { return invicibilityTimer > 0; } //Métode pour vérifier l'invincibilité
    void setScreenBounds(int width, int height);
};