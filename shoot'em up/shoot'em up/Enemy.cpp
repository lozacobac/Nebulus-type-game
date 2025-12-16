#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(float px, float py,int sw, int sh) :
    x(px),
    y(py),
    rect({ x, y, 32, 32 }),
    moveTimer(0.0f),
    shotTimer(0.0f),
    screenWidth(sw),
    screenHeight(sh)
{
}


bool Enemy::checkCollision(const SDL_FRect& other) {
    return SDL_HasRectIntersectionFloat(&rect, &other);
}

BasicEnemy::BasicEnemy(float px, float py,int sw,int sh) : Enemy(px, py,sw,sh) {}

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
        if (it->isOffScreen(screenWidth, screenHeight))
            it = projectiles.erase(it);
        else ++it;
    }
}

void BasicEnemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 62, 137, 134, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    for (auto& p : projectiles) SDL_RenderFillRect(renderer, &p.rect);
}

int BasicEnemy::getType() const { return 23; }

ZigzagEnemy::ZigzagEnemy(float px, float py, int sw, int sh) : Enemy(px, py,sw,sh) {}

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
        if (it->isOffScreen(screenWidth, screenHeight))
            it = projectiles.erase(it);
        else ++it;
    }
}


void ZigzagEnemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 58, 164, 118, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    for (auto& p : projectiles) SDL_RenderFillRect(renderer, &p.rect);
}

int ZigzagEnemy::getType() const { return 24; }

Drowned::Drowned(float px, float py, int sw, int sh) : Enemy(px, py, sw, sh) {}

void Drowned::update(float deltaTime, Player& player)
{
    y += 50.f * deltaTime;
    float vx = 0.0f;
    float dx = player.x - x;
    float distance = sqrt(dx * dx);

    if (distance > 0.0f) {
        float speed = 500.0f;
        float targetVx = (dx / distance) * speed;
        float homingStrength = 5.0f;
        vx += (targetVx - vx) * homingStrength * deltaTime;
        x += vx * deltaTime;
    }

    rect.x = x;
    rect.y = y;

    static float shotTimer = 0.0f;
    shotTimer += deltaTime;
    if (shotTimer >= 1.5f) {
        projectiles.push_back({
            x + 12,
            y + 32,
            0,
            250.0f,
            false,
            {x + rect.w / 2 - 4, y + rect.h, 8, 8}
            });
        shotTimer = 0.0f;
    }
    for (auto it = projectiles.begin();
        it != projectiles.end(); ) {

        it->update(deltaTime);
        if (it->isOffScreen(screenWidth, screenHeight))
            it = projectiles.erase(it);
        else ++it;
    }
}

void Drowned::render(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 62, 137, 134, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    for (auto& p : projectiles) SDL_RenderFillRect(renderer, &p.rect);
}

int Drowned::getType() const { return 1; }


Guardian::Guardian(float px, float py, int sw, int sh) : Enemy(px, py, sw, sh) {}

void Guardian::update(float deltaTime, Player& player) {
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
        if (it->isOffScreen(screenWidth, screenHeight))
            it = projectiles.erase(it);
        else ++it;
    }
}

void Guardian::render(SDL_Renderer* renderer)
{
}

int Guardian::getType() const { return 2; }

Elder_Guardian::Elder_Guardian(float px, float py, int sw, int sh) : Enemy(px, py, sw, sh) {}

void Elder_Guardian::update(float delatTime, Player& player)
{
}

void Elder_Guardian::render(SDL_Renderer* renderer)
{
}

int Elder_Guardian::getType() const { return 3; }

SkeletonEnemy::SkeletonEnemy(float px, float py, int sw, int sh) : Enemy(px, py, sw, sh) {}

void SkeletonEnemy::update(float deltaTime, Player& player) {
    y += 50.0f * deltaTime;
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
        if (it->isOffScreen(screenWidth, screenHeight))
            it = projectiles.erase(it);
        else ++it;
    }
}

void SkeletonEnemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 206, 206, 206, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_FlushRenderer(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    for (auto& p : projectiles) SDL_RenderFillRect(renderer, &p.rect);
}

int SkeletonEnemy::getType() const { return 4; }

BlazeEnemy::BlazeEnemy(float px, float py, int sw, int sh) : Enemy(px, py, sw, sh) {}

void BlazeEnemy::update(float deltaTime, Player& player) {
    y += 100.0f * deltaTime;
    rect.x = x;
    rect.y = y;

    static float shotTimer = 0.0f;
    shotTimer += deltaTime;
    if (shotTimer >= 2.0f) {
        float dx = player.x - x;
        float dy = player.y - y;
        float distance = sqrt(dx * dx + dy * dy);
        float speed = 200.0f;
        float vx = (dx / distance) * speed;
        float vy = (dy / distance) * speed;
        projectiles.push_back({
            x + rect.w/2-4,
            y + rect.h,
            vx,
            vy,
            false,
            {x + rect.w / 2 - 4,y + rect.h,8,8}
            });
        shotTimer = 0.0f;
    }
    for (auto it = projectiles.begin();
        it != projectiles.end(); ) {

        it->update(deltaTime);
        if (it->isOffScreen(screenWidth, screenHeight))
            it = projectiles.erase(it);
        else ++it;
    }
}

void BlazeEnemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 109, 31, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    for (auto& p : projectiles) SDL_RenderFillRect(renderer, &p.rect);
}

int BlazeEnemy::getType() const { return 5; }

ShulkerEnemy::ShulkerEnemy(float px, float py, int sw, int sh) : Enemy(px, py, sw, sh),
    invulnerabilityTimer(0.0f),
    isInvulnerable(false)
{
}

void ShulkerEnemy::update(float deltaTime, Player& player) {
    y += 50.0f * deltaTime;
    rect.x = x;
    rect.y = y;

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
        
        float distance = sqrt(dx * dx);

        // Normalisation et application de la vitesse
        
        projectiles.push_back({
            x + rect.w / 2 - 4,
            y + rect.h,
            0,
            200.0,
            false,
            {x + rect.w / 2 - 4, y + rect.h, 8, 8}
            });
        shotTimer = 0.0f;
    }

    // Mise � jour des projectiles avec guidage
    for (auto it = projectiles.begin(); it != projectiles.end(); ) {
        // Guidage vers le joueur
        float dx = player.x - it->x;
        float dy = player.y - it->y;
        float distance = sqrt(dx * dx);

        float minHomingDistance = 400.0f;

        if (distance > minHomingDistance) {
            float homingStrength = 100.0f;

            // Direction vers le joueur
            float targetVx = (dx / distance) * 200.0f;
            float targetVy = (dy / distance) * 200.0f;

            // Interpolation vers la direction cible
            it->vx += (targetVx - it->vx) * homingStrength * deltaTime / 200.0f;
            it->vy += (targetVy - it->vy) * homingStrength * deltaTime / 200.0f;
        }
        // Sinon, le projectile continue en ligne droite

        it->update(deltaTime);

        if (it->isOffScreen(screenWidth, screenHeight))
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

DragonEnemy::DragonEnemy(float px, float py, int sw, int sh) : Enemy(px, py,sw,sh) {
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
    }
    for (auto it = projectiles.begin();
        it != projectiles.end(); ) {

        it->update(deltaTime);
        if (it->isOffScreen(screenWidth, screenHeight))
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

Enderman::Enderman(float px, float py, int sw, int sh) : Enemy(px, py, sw, sh) {}

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

PhantomEnemy::PhantomEnemy(float px, float py, int sw, int sh) : Enemy(px, py, sw, sh) {}

void PhantomEnemy::update(float deltaTime, Player& player) {
    y += 150.0f * deltaTime;
    moveTimer += deltaTime;
    x += sin(moveTimer * 10.0f) * 200.0f * deltaTime;
    rect.x = x;
    rect.y = y;

    static float shotTimer = 0.0f;
    shotTimer += deltaTime;
    if (shotTimer >= 0.6f) {
        projectiles.push_back({
            x + 12,
            y + 32,
            0,
            350.0f,
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
        if (it->isOffScreen(screenWidth, screenHeight))
            it = projectiles.erase(it);
        else ++it;
    }
}

void PhantomEnemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 191, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    for (auto& p : projectiles) SDL_RenderFillRect(renderer, &p.rect);
}

int PhantomEnemy::getType() const { return 10; }

SculkEnemy::SculkEnemy(float px, float py, int sw, int sh) : Enemy(px, py, sw, sh) {}

void SculkEnemy::update(float deltaTime, Player& player) {
    y += 150.0f * deltaTime;
    moveTimer += deltaTime;
    x += sin(moveTimer * 7.0f) * 200.0f * deltaTime;
    rect.x = x; rect.y = y;

    static float shotTimer = 0.0f;
    shotTimer += deltaTime;
    if (shotTimer >= 0.6f) {
        projectiles.push_back({
            x + 12,
            y + 32,
            0,
            350.0f,
            false,
            {x + rect.w / 2 - 4,
            y + rect.h,
            8,
            8} });
        projectiles.push_back({
            x + 12,
            y + 32,
            -50,
            350.0f,
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
        if (it->isOffScreen(screenWidth, screenHeight))
            it = projectiles.erase(it);
        else ++it;
    }
}

void SculkEnemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 139, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    for (auto& p : projectiles) SDL_RenderFillRect(renderer, &p.rect);
}

int SculkEnemy::getType() const { return 11; }

WardenBoss::WardenBoss(float px, float py, int sw, int sh, int& wardenHealthRef) : Enemy(px, py, sw, sh), wardenHealthRef(wardenHealthRef) {
    maxHealth = 200;  // Santé max pour calculer les phases
    rect.w = 120;
    rect.h = 100;
}


void WardenBoss::update(float deltaTime, Player& player) {
    moveTimer += deltaTime;
    static float changeDirectionTimer = 0.0f;
    static float direction = -1.0f;
    changeDirectionTimer += deltaTime;
    random rd;

    // Utilise wardenHealthRef pour calculer les phases (liaison correcte avec LevelBase)
    float healthPercent = (float)wardenHealthRef / (float)maxHealth;
    int currentPhase = 0;
    if (healthPercent <= 0.75f) currentPhase = 1;  // 150 HP
    if (healthPercent <= 0.50f) currentPhase = 2;  // 100 HP
    if (healthPercent <= 0.25f) currentPhase = 3;  // 50 HP
    if (healthPercent <= 0.10f) currentPhase = 4;  // 20 HP

    float directionChangeDelay = 1.5f - (currentPhase * 0.2f);
    if (changeDirectionTimer >= directionChangeDelay + rd.getRandomNumber(0, 99) / 100.0f) {  // Plage 0-99 pour /100.0f
        int randomChoice = rd.getRandomNumber(0, 2);
        if (randomChoice == 0) direction = -1.0f;
        else if (randomChoice == 1) direction = 1.0f;
        else direction = 0.0f;
        changeDirectionTimer = 0.0f;
    }

    float baseSpeed = 100 + (currentPhase * 100);
    float speed = rd.getRandomNumber(baseSpeed, baseSpeed + 399);  // Plage baseSpeed à baseSpeed+399
    x += direction * speed * deltaTime;

    if (x < 0) x = 0;
    else if (x + rect.w > screenWidth) x = screenWidth - rect.w;
    rect.x = x;
    rect.y = y;

    static float shotTimer = 0.0f;
    static float specialAttackTimer = 0.0f;
    static float spiralTimer = 0.0f;

    shotTimer += deltaTime;
    specialAttackTimer += deltaTime;
    spiralTimer += deltaTime;

    // Valeurs par défaut (Phase 0)
    float shotDelay = 0.8f;
    int numProjectiles = 5;
    float spreadAngle = 0.5f;

    // Phase 1
    if (currentPhase >= 1) {
        shotDelay = 0.6f;
        numProjectiles = 7;
        spreadAngle = 0.7f;
    }

    // Phase 2
    if (currentPhase >= 2) {
        shotDelay = 0.4f;
        numProjectiles = 9;
        spreadAngle = 0.9f;

        if (specialAttackTimer >= 3.0f) {
            for (int i = 0; i < 8; i++) {
                float angle = (i / 8.0f) * 3.14159f * 2;
                projectiles.push_back({
                    x + rect.w / 2,
                    y + rect.h / 2,
                    cos(angle) * 200.0f,
                    sin(angle) * 200.0f,
                    false,
                    {x + rect.w / 2 - 6, y + rect.h / 2 - 6, 12, 12}
                    });
            }
            specialAttackTimer = 0.0f;
        }
    }

    // Phase 3
    if (currentPhase >= 3) {
        shotDelay = 0.2f;
        numProjectiles = 0;
        spreadAngle = 1.2f;

        if (spiralTimer >= 0.1f) {
            static float spiralAngle = 0.0f;
            spiralAngle += 0.3f;
            for (int i = 0; i < 3; i++) {
                float angle = spiralAngle + (i * 3.14159f * 2 / 3);
                projectiles.push_back({
                    x + rect.w / 2,
                    y + rect.h / 2,
                    cos(angle) * 150.0f,
                    sin(angle) * 150.0f,
                    false,
                    {x + rect.w / 2 - 5, y + rect.h / 2 - 5, 10, 10}
                    });
            }
            spiralTimer = 0.0f;
        }

        if (specialAttackTimer >= 2.0f) {
            for (int i = 0; i < 12; i++) {
                float angle = (i / 12.0f) * 3.14159f * 2;
                projectiles.push_back({
                    x + rect.w / 2,
                    y + rect.h / 2,
                    cos(angle) * 250.0f,
                    sin(angle) * 250.0f,
                    false,
                    {x + rect.w / 2 - 6, y + rect.h / 2 - 6, 12, 12}
                    });
            }
            specialAttackTimer = 0.0f;
        }
    }

    // Phase 4 (berserk)
    if (currentPhase >= 4) {
        shotDelay = 0.1f;
        numProjectiles = 0;
        spreadAngle = 1.5f;

        if (spiralTimer >= 0.05f) {
            static float spiralAngle = 0.0f;
            spiralAngle += 0.5f;
            for (int i = 0; i < 5; i++) {
                float angle = spiralAngle + (i * 3.14159f * 2 / 5);
                projectiles.push_back({
                    x + rect.w / 2,
                    y + rect.h / 2,
                    cos(angle) * 300.0f,
                    sin(angle) * 300.0f,
                    false,
                    {x + rect.w / 2 - 7, y + rect.h / 2 - 7, 14, 14}
                    });
            }
            spiralTimer = 0.0f;
        }

        if (specialAttackTimer >= 1.5f) {
            for (int i = 0; i < 16; i++) {
                float angle = (i / 16.0f) * 3.14159f * 2;
                projectiles.push_back({
                    x + rect.w / 2,
                    y + rect.h / 2,
                    cos(angle) * 300.0f,
                    sin(angle) * 300.0f,
                    false,
                    {x + rect.w / 2 - 8, y + rect.h / 2 - 8, 16, 16}
                    });
            }
            specialAttackTimer = 0.0f;
        }
    }

    // Tir principal
    if (shotTimer >= shotDelay) {
        for (int i = 0; i < numProjectiles; i++) {
            float angle = (i - (numProjectiles - 1) / 2.0f) * spreadAngle;
            projectiles.push_back({
                x + rect.w / 2,
                y + rect.h,
                sin(angle) * 100.0f,
                400.0f + (currentPhase * 50.0f),
                false,
                {x + rect.w / 2 - 4 + i * 10, y + rect.h, 8, 8}
                });
        }
        shotTimer = 0.0f;
    }

    // Update projectiles
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        it->update(deltaTime);
        if (it->isOffScreen(screenWidth, screenHeight))
            it = projectiles.erase(it);
        else ++it;
    }
}

void WardenBoss::render(SDL_Renderer* renderer) {
    // Utilise wardenHealthRef pour les couleurs (liaison correcte)
    float healthPercent = (float)wardenHealthRef / (float)maxHealth;

    if (healthPercent > 0.75f) {
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // Gris foncé
    }
    else if (healthPercent > 0.50f) {
        SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255); // Rouge sombre
    }
    else if (healthPercent > 0.25f) {
        SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255); // Rouge
    }
    else if (healthPercent > 0.10f) {
        SDL_SetRenderDrawColor(renderer, 200, 50, 0, 255); // Orange-rouge
    }
    else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rouge vif (berserk)
    }

    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (auto& p : projectiles) SDL_RenderFillRect(renderer, &p.rect);
}

int WardenBoss::getType() const { return 12; }

std::unique_ptr<Enemy> createEnemy(int type, float x, float y, int screenWidth, int screenHeight) {
    if (type == 23) return std::make_unique<BasicEnemy>(x, y, screenWidth, screenHeight);
    else if (type == 24) return std::make_unique<ZigzagEnemy>(x, y, screenWidth, screenHeight);
    else if (type == 1) return std::make_unique<Drowned>(x, y, screenWidth, screenHeight);
    else if (type == 2) return std::make_unique<Guardian>(x, y, screenWidth, screenHeight);
    else if (type == 3) return std::make_unique<Elder_Guardian>(x, y, screenWidth, screenHeight);
    else if (type == 4) return std::make_unique<SkeletonEnemy>(x, y, screenWidth, screenHeight);
    else if (type == 5) return std::make_unique<BlazeEnemy>(x, y, screenWidth, screenHeight);
    else if (type == 7) return std::make_unique<ShulkerEnemy>(x, y, screenWidth, screenHeight);
    else if (type == 8) return std::make_unique<Enderman>(x, y, screenWidth, screenHeight);
    else if (type == 9) return std::make_unique<DragonEnemy>(x, y, screenWidth, screenHeight);
    else if (type == 10) return std::make_unique<PhantomEnemy>(x, y, screenWidth, screenHeight);
    else if (type == 11) return std::make_unique<SculkEnemy>(x, y, screenWidth, screenHeight);
    // Retiré : else if (type == 12) return std::make_unique<WardenBoss>(x, y, screenWidth, screenHeight);
    return nullptr;
}