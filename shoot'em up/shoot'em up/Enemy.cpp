#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(float px, float py) : 
    x(px), 
    y(py), 
    rect({ x, y, 32, 32 }), 
    moveTimer(0.0f),
    shotTimer(0.0f)
{}

bool Enemy::checkCollision(const SDL_FRect& other) {
    return SDL_HasRectIntersectionFloat(&rect, &other);
}

BasicEnemy::BasicEnemy(float px, float py) : Enemy(px, py) {}

void BasicEnemy::update(float deltaTime, Player& player) {
    y += 100.0f * deltaTime;
    rect.x = x;
    rect.y = y;

    static float shotTimer = 0.0f;
    shotTimer += deltaTime;
    if (shotTimer >= 2.0f) {
        projectiles.push_back({ 
            x + 12, 
            y + 32, 
            0, 
            200.0f, 
            false, 
            {x + rect.w / 2 - 4,y + rect.h,8,8}
        });
        shotTimer = 0.0f;
    }
    for (auto it = projectiles.begin();
        it != projectiles.end(); ) {

        it->update(deltaTime);
        if (it->isOffScreen(800, 600))
            it = projectiles.erase(it);
        else ++it;
    }
}

void BasicEnemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    for (auto& p : projectiles) SDL_RenderFillRect(renderer, &p.rect);
}

int BasicEnemy::getType() const { return 1; }

ZigzagEnemy::ZigzagEnemy(float px, float py) : Enemy(px, py) {}

void ZigzagEnemy::update(float deltaTime, Player& player) {
    y += 100.0f * deltaTime;
    moveTimer += deltaTime;
    x += sin(moveTimer * 5.0f) * 150.0f * deltaTime;
    rect.x = x; rect.y = y;

    static float shotTimer = 0.0f;
    shotTimer += deltaTime;
    if (shotTimer >= 1.0f) {
        projectiles.push_back({ 
            x + 12, 
            y + 32, 
            0,
            250.0f,
            false,
            {x + rect.w / 2 - 4,
            y + rect.h,
            8,
            8} });
        shotTimer = 0.0f;
    }
    for (auto it = projectiles.begin();
        it != projectiles.end(); ) {

        it->update(deltaTime);
        if (it->isOffScreen(800, 600))
            it = projectiles.erase(it);
        else ++it;
    }
}


void ZigzagEnemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    for (auto& p : projectiles) SDL_RenderFillRect(renderer, &p.rect);
}

int ZigzagEnemy::getType() const { return 2; }

std::unique_ptr<Enemy> createEnemy(int type, float x, float y) {
    if (type == 1) return std::make_unique<BasicEnemy>(x, y);
    else if (type == 2) return std::make_unique<ZigzagEnemy>(x, y);
    return nullptr;
}