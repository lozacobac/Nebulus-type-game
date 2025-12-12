#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(float px, float py) :
    x(px),
    y(py),
    rect({ x, y, 32, 32 }),
    moveTimer(0.0f),
    shotTimer(0.0f)
{
}


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

ShulkerEnemy::ShulkerEnemy(float px, float py)
    : Enemy(px, py),
    invulnerabilityTimer(0.0f),
    isInvulnerable(false)
{
}

void ShulkerEnemy::update(float deltaTime, Player& player) {
    y += 50.0f * deltaTime;
    rect.x = x;
    rect.y = y;

    // Gestion du cycle d'invulnérabilité
    invulnerabilityTimer += deltaTime;

    if (invulnerabilityTimer < 2.0f) {
        isInvulnerable = false;
    }
    else if (invulnerabilityTimer < 4.0f) {
        isInvulnerable = true;
    }
    else {
        invulnerabilityTimer = 0.0f;
    }

    static float shotTimer = 0.0f;
    shotTimer += deltaTime;
    if (shotTimer >= 5.0f) {
        // Calcul de la direction vers le joueur
        float dx = player.x - x;
        float dy = player.y - y;
        float distance = sqrt(dx * dx + dy * dy);

        // Normalisation et application de la vitesse
        float speed = 150.0f;
        float vx = (dx / distance) * speed;
        float vy = (dy / distance) * speed;

        projectiles.push_back({
            x + rect.w / 2 - 4,
            y + rect.h,
            vx,  // Vitesse en X vers le joueur
            vy,  // Vitesse en Y vers le joueur
            false,
            {x + rect.w / 2 - 4, y + rect.h, 8, 8}
            });
        shotTimer = 0.0f;
    }

    // Mise à jour des projectiles avec guidage
    for (auto it = projectiles.begin(); it != projectiles.end(); ) {
        // Guidage vers le joueur
        float dx = player.x - it->x;
        float dy = player.y - it->y;
        float distance = sqrt(dx * dx + dy * dy);

        float minHomingDistance = 150.0f;

        if (distance > minHomingDistance) {
            float homingStrength = 100.0f;

            // Direction vers le joueur
            float targetVx = (dx / distance) * 150.0f;
            float targetVy = (dy / distance) * 150.0f;

            // Interpolation vers la direction cible
            it->vx += (targetVx - it->vx) * homingStrength * deltaTime / 150.0f;
            it->vy += (targetVy - it->vy) * homingStrength * deltaTime / 150.0f;
        }
        // Sinon, le projectile continue en ligne droite

        it->update(deltaTime);

        if (it->isOffScreen(800, 600))
            it = projectiles.erase(it);
        else
            ++it;
    }
}

void ShulkerEnemy::render(SDL_Renderer* renderer) {
    if (isInvulnerable) {
        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 100, 100, 0, 255);
    }

    SDL_RenderFillRect(renderer, &rect);


    SDL_SetRenderDrawColor(renderer, 200, 0, 255, 255);
    for (auto& p : projectiles)
        SDL_RenderFillRect(renderer, &p.rect);
}

bool ShulkerEnemy::checkCollision(const SDL_FRect& other) {
    if (isInvulnerable) {
        return false;
    }
    return SDL_HasRectIntersectionFloat(&rect, &other);
}

int ShulkerEnemy::getType() const { return 7; }

DragonEnemy::DragonEnemy(float px, float py) : Enemy(px, py) {
    rect.w = 180;
    rect.h = 250;
}

void DragonEnemy::update(float deltaTime, Player& player) {


    static float shotTimer = 0.0f;
    shotTimer += deltaTime;
    if (shotTimer >= 2.0f) {
        projectiles.push_back({
            x + 80,
            y + 250,
            0,
            300.0f,
            false,
            {x + rect.w / 2 - 4,y + rect.h,8,8}
            });
        shotTimer = 0.0f;
        projectiles.push_back({
            x + 100,
            y + 250,
            0,
            300.0f,
            false,
            {x + rect.w / 2 - 4,y + rect.h,8,8}
            });
        shotTimer = 0.0f;
        projectiles.push_back({
            x + 0,
            y + 250,
            0,
            500.0f,
            false,
            {x + rect.w / 2 - 4,y + rect.h,8,8}
            });
        shotTimer = 0.0f;
        projectiles.push_back({
            x + 10,
            y + 250,
            0,
            500.0f,
            false,
            {x + rect.w / 2 - 4,y + rect.h,8,8}
            });
        shotTimer = 0.0f;
        projectiles.push_back({
            x + 180,
            y + 250,
            0,
            500.0f,
            false,
            {x + rect.w / 2 - 4,y + rect.h,8,8}
            });
        shotTimer = 0.0f;
        projectiles.push_back({
            x + 170,
            y + 250,
            0,
            500.0f,
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

void DragonEnemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    for (auto& p : projectiles) SDL_RenderFillRect(renderer, &p.rect);
}

int DragonEnemy::getType() const { return 9; }

Enderman::Enderman(float px, float py) : Enemy(px, py) {}

void Enderman::update(float deltaTime, Player& player) {
    y += 100.0f * deltaTime;
    rect.x = x;
    rect.y = y;
}

void Enderman::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 30, 90, 160);
    SDL_RenderFillRect(renderer, &rect);
    for (auto& p : projectiles) SDL_RenderFillRect(renderer, &p.rect);
}

int Enderman::getType() const { return 8; }



std::unique_ptr<Enemy> createEnemy(int type, float x, float y) {
    if (type == 1) return std::make_unique<BasicEnemy>(x, y);
    else if (type == 2) return std::make_unique<ZigzagEnemy>(x, y);
    else if (type == 7) return std::make_unique<ShulkerEnemy>(x, y);
    else if (type == 8) return std::make_unique<Enderman>(x, y);
    else if (type == 9) return std::make_unique<DragonEnemy>(x, y);
    return nullptr;
}