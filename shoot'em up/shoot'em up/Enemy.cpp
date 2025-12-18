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
        float speed = 100.0f;
        float targetVx = (dx / distance) * speed;
        float homingStrength = 5.0f;
        vx += (targetVx - vx) * homingStrength * deltaTime;
        x += vx * deltaTime;
    }

    rect.x = x;
    rect.y = y;

    static float shotTimer = 1.5f;
    shotTimer += deltaTime;
    if (shotTimer >= 2.0f) {
        projectiles.push_back({
            x + 12,
            y + 32,
            0,
            250.0f,
            false,
            {x + rect.w / 2 - 4, y + rect.h, 8, 8}
            });
        shotTimer = 1.5f;
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
    y += 50.0f * deltaTime;
    rect.x = x;
    rect.y = y;

    phaseTimer += deltaTime;
    if (currentPhase == BURST) {
        shotTimer += deltaTime;
        if (shotTimer >= 0.001f) {
            float dx = player.x - x;
            float dy = player.y - y;
            float distance = sqrt(dx * dx + dy * dy);
            float speed = 200.0f;
            float vx = (dx / distance) * speed;
            float vy = (dy / distance) * speed;
            projectiles.push_back({
                x + rect.w / 2 - 4,
                y + rect.h,
                vx,
                vy,
                false,
                {x + rect.w / 2 - 4,y + rect.h,8,8}
                });
            shotTimer = 0.0f;
        }

        if (phaseTimer >= 1.5f) {
            currentPhase = PAUSE;
            phaseTimer = 0.0f;
            shotTimer = 0.0f;
        }
    }
    else {
        if (phaseTimer >= 2.0f) {
            currentPhase = BURST;
            phaseTimer = 0.0f;
        }
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
    SDL_SetRenderDrawColor(renderer, 62, 137, 134, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    for (auto& p : projectiles) SDL_RenderFillRect(renderer, &p.rect);
}

int Guardian::getType() const { return 2; }

Elder_Guardian::Elder_Guardian(float px, float py, int sw, int sh) : Enemy(px, py, sw, sh) {}

void Elder_Guardian::update(float deltaTime, Player& player)
{
    rect.w = 150;
    rect.h = 200;

    phaseTimer += deltaTime;
    if (currentPhase == BURST) {
        shotTimer += deltaTime;
        if (shotTimer >= 0.001f) {
            float dx = player.x - x;
            float dy = player.y - y;
            float distance = sqrt(dx * dx + dy * dy);
            float speed = 200.0f;
            float vx = (dx / distance) * speed;
            float vy = (dy / distance) * speed;
            projectiles.push_back({
                x + rect.w / 2 - 4,
                y + rect.h,
                vx,
                vy,
                false,
                {x + rect.w / 2 ,y + rect.h,8,8}
                });
            shotTimer = 0.0f;
        }

        if (phaseTimer >= 1.5f) {
            currentPhase = PAUSE;
            phaseTimer = 0.0f;
            shotTimer = 0.0f;
        }
    }
    else {
        if (phaseTimer >= 2.0f) {
            currentPhase = BURST;
            phaseTimer = 0.0f;
        }
    }
    for (auto it = projectiles.begin();
        it != projectiles.end(); ) {

        it->update(deltaTime);
        if (it->isOffScreen(screenWidth, screenHeight))
            it = projectiles.erase(it);
        else ++it;
    }
}

void Elder_Guardian::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 62, 137, 134, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    for (auto& p : projectiles) SDL_RenderFillRect(renderer, &p.rect);
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

    if (invulnerabilityTimer < 3.0f) {
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
        if (player.y > y) {
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
            vx,
            vy,
            false,
            {x + rect.w / 2 - 4, y + rect.h, 8, 8}
                });
        }
        shotTimer = 0.0f;

        
    }

    // Mise a jour des projectiles avec guidage
    for (auto it = projectiles.begin(); it != projectiles.end(); ) {
        // Guidage vers le joueur
        float dx = player.x - it->x;
        float dy = player.y - it->y;
        float distance = sqrt(dx * dx + dy * dy);

        float minHomingDistance = 800.0f;

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

DragonBoss::DragonBoss(float px, float py, int sw, int sh) : Enemy(px, py,sw,sh) {
    rect.w = 180;
    rect.h = 250;
}

void DragonBoss::update(float deltaTime, Player& player) {


    static float shotTimer = 0.0f;
    shotTimer += deltaTime;
    if (shotTimer >= 2.0f) {
        projectiles.push_back({
            x + 80,
            y + 250,
            0,
            350.0f,
            false,
            {x + rect.w / 2 - 4,
            y + rect.h,
            8,
            8} });
        shotTimer = 0.0f;
        projectiles.push_back({
            x + 100,
            y + 250,
            0,
            350.0f,
            false,
            {x + rect.w / 2 - 4,
            y + rect.h,
            8,
            8} });
        shotTimer = 0.0f;
        projectiles.push_back({
            x + 0,
            y + 250,
            0,
            450.0f,
            false,
            {x + rect.w / 2 - 4,
            y + rect.h,
            8,
            8} });
        shotTimer = 0.0f;
        projectiles.push_back({
            x + 10,
            y + 250,
            0,
            450.0f,
            false,
            {x + rect.w / 2 - 4,
            y + rect.h,
            8,
            8} });
        shotTimer = 0.0f;
        projectiles.push_back({
            x + 180,
            y + 250,
            0,
            450.0f,
            false,
            {x + rect.w / 2 - 4,
            y + rect.h,
            8,
            8} });
        shotTimer = 0.0f;
        projectiles.push_back({
            x + 170,
            y + 250,
            0,
            450.0f,
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

void DragonBoss::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    for (auto& p : projectiles) SDL_RenderFillRect(renderer, &p.rect);
}

int DragonBoss::getType() const { return 9; }

EndermanEnemy::EndermanEnemy(float px, float py, int sw, int sh) : Enemy(px, py, sw, sh) {}

void EndermanEnemy::update(float deltaTime, Player& player) {
    y += 100.0f * deltaTime;
    rect.x = x;
    rect.y = y;
}

void EndermanEnemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 30, 90, 160);
    SDL_RenderFillRect(renderer, &rect);
    for (auto& p : projectiles) SDL_RenderFillRect(renderer, &p.rect);
}

int EndermanEnemy::getType() const { return 8; }

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
    maxHealth = 150;  // NERF : Réduit de 200 à 150 pour le rendre plus vulnérable
    rect.w = 120;
    rect.h = 100;
}

void WardenBoss::update(float deltaTime, Player& player) {
    moveTimer += deltaTime;
    static float changeDirectionTimer = 0.0f;
    static float direction = -1.0f;
    changeDirectionTimer += deltaTime;
    random rd;

    // Calcul des phases basé sur la santé actuelle
    int currentPhase = 0;
    if (wardenHealthRef <= 120) currentPhase = 1;  // NERF : Phases ajustées pour commencer plus tôt
    if (wardenHealthRef <= 80) currentPhase = 2;
    if (wardenHealthRef <= 40) currentPhase = 3;
    if (wardenHealthRef <= 15) currentPhase = 4;  // NERF : Phase finale plus tôt

    // Mouvement (NERF : Vitesse réduite et délai augmenté pour changer de direction)
    float directionChangeDelay = 1.5f - (currentPhase * 0.1f);  // Augmenté de 1.2f à 1.5f
    if (changeDirectionTimer >= directionChangeDelay + rd.getRandomNumber(0, 80) / 100.0f) {
        int randomChoice = rd.getRandomNumber(0, 3);
        if (randomChoice == 0) direction = -1.0f;
        else if (randomChoice == 1) direction = 1.0f;
        else direction = 0.0f;
        changeDirectionTimer = 0.0f;
    }

    float baseSpeed = 100 + (currentPhase * 50);  // NERF : Réduit de 120 à 100, et augmentation par phase réduite
    float speed = rd.getRandomNumber(baseSpeed, baseSpeed + 200);  // Plage réduite
    x += direction * speed * deltaTime;

    if (x < 0) x = 0;
    else if (x + rect.w > screenWidth) x = screenWidth - rect.w;
    rect.x = x;
    rect.y = y;

    static float shotTimer = 0.0f;
    static float specialAttackTimer = 0.0f;
    static float spiralTimer = 0.0f;
    static float waveTimer = 0.0f;
    // NOUVEAU : Timers pour spawns de Phantom et Sculk
    static float phantomSpawnTimer = 0.0f;
    static float sculkSpawnTimer = 0.0f;

    shotTimer += deltaTime;
    specialAttackTimer += deltaTime;
    spiralTimer += deltaTime;
    waveTimer += deltaTime;
    phantomSpawnTimer += deltaTime;
    sculkSpawnTimer += deltaTime;

    // PHASE 0 - Pattern de base (NERF : Moins de projectiles, délai plus long)
    float shotDelay = 0.9f;  // Augmenté de 0.7f
    int numProjectiles = 4;  // Réduit de 5
    float spreadAngle = 0.5f;  // Réduit de 0.6f

    // PHASE 1 - Augmentation intensité (120 HP ou moins) (NERF : Moins agressif)
    if (currentPhase >= 1) {
        shotDelay = 0.6f;  // Augmenté de 0.5f
        numProjectiles = 5;  // Réduit de 7
        spreadAngle = 0.6f;  // Réduit de 0.8f

        // Vagues en colonnes (NERF : Moins de colonnes, délai plus long)
        if (waveTimer >= 3.0f) {  // Augmenté de 2.5f
            int numColumns = 4;  // Réduit de 5
            float columnSpacing = screenWidth / (numColumns + 1.0f);

            for (int col = 0; col < numColumns; col++) {
                float xPos = columnSpacing * (col + 1);
                projectiles.push_back({
                    xPos,
                    y + rect.h / 2,
                    0.0f,
                    200.0f,  // Réduit de 250.0f
                    false,
                    {xPos - 8, y + rect.h / 2 - 8, 16, 16}
                    });
            }
            waveTimer = 0.0f;
        }
    }

    // PHASE 2 - Dangereux (80 HP ou moins) (NERF : Patterns moins denses)
    if (currentPhase >= 2) {
        shotDelay = 0.5f;  // Augmenté de 0.4f
        numProjectiles = 0;  // Réduit de 9
        spreadAngle = 0.8f;  // Réduit de 1.0f

        // Spirale lente avec gaps (NERF : Moins de projectiles, délai plus long)
        if (spiralTimer >= 0.2f) {  // Augmenté de 0.15f
            static float spiralAngle = 0.0f;
            spiralAngle += 0.4f;  // Réduit de 0.5f

            // Seulement 3 projectiles au lieu de 4 pour plus de gaps
            for (int i = 0; i < 3; i++) {
                float angle = spiralAngle + (i * 3.14159f * 2 / 3);
                projectiles.push_back({
                    x + rect.w / 2,
                    y + rect.h / 2,
                    cos(angle) * 120.0f,  // Réduit de 150.0f
                    sin(angle) * 120.0f,
                    false,
                    {x + rect.w / 2 - 6, y + rect.h / 2 - 6, 12, 12}
                    });
            }
            spiralTimer = 0.0f;
        }

        // Cercle avec gaps (NERF : Moins de projectiles, délai plus long)
        if (specialAttackTimer >= 4.0f) {  // Augmenté de 3.0f
            // 10 projectiles au lieu de 12
            for (int i = 0; i < 10; i++) {
                float angle = (i / 10.0f) * 3.14159f * 2;
                projectiles.push_back({
                    x + rect.w / 2,
                    y + rect.h / 2,
                    cos(angle) * 180.0f,  // Réduit de 200.0f
                    sin(angle) * 180.0f,
                    false,
                    {x + rect.w / 2 - 6, y + rect.h / 2 - 6, 12, 12}
                    });
            }
            specialAttackTimer = 0.0f;
        }
    }

    // PHASE 3 - Difficile mais fair (40 HP ou moins) (NERF : Plus de gaps)
    if (currentPhase >= 3) {
        shotDelay = 0.3f;  // Augmenté de 0.2f
        numProjectiles = 0;  // Réduit de 11
        spreadAngle = 1.0f;  // Réduit de 1.2f

        // Double spirale alternée (NERF : Moins de projectiles par spirale)
        if (spiralTimer >= 0.15f) {  // Augmenté de 0.12f
            static float spiralAngle = 0.0f;
            spiralAngle += 0.5f;  // Réduit de 0.6f

            // 2 spirales de 2 projectiles chacune
            for (int spiral = 0; spiral < 2; spiral++) {
                for (int i = 0; i < 2; i++) {
                    float angle = spiralAngle + (i * 3.14159f) + (spiral * 3.14159f / 2);
                    projectiles.push_back({
                        x + rect.w / 2,
                        y + rect.h / 2,
                        cos(angle) * (150.0f + spiral * 20.0f),  // Réduit
                        sin(angle) * (150.0f + spiral * 20.0f),
                        false,
                        {x + rect.w / 2 - 6, y + rect.h / 2 - 6, 12, 12}
                        });
                }
            }
            spiralTimer = 0.0f;
        }

        // Pattern "rideau" (NERF : Moins de colonnes)
        if (specialAttackTimer >= 3.0f) {  // Augmenté de 2.5f
            int numCols = 5;  // Réduit de 6
            float spacing = screenWidth / (numCols + 1.0f);

            for (int i = 0; i < numCols; i++) {
                float xPos = spacing * (i + 1);
                projectiles.push_back({
                    xPos,
                    y + rect.h / 2,
                    0.0f,
                    250.0f,  // Réduit de 300.0f
                    false,
                    {xPos - 8, y + rect.h / 2 - 8, 16, 16}
                    });
            }
            specialAttackTimer = 0.0f;
        }
    }

    // PHASE 4 - FINALE INTENSE MAIS JOUABLE (15 HP ou moins) (NERF : Plus de gaps, vitesses réduites)
    if (currentPhase >= 4) {
        shotDelay = 0.2f;  // Augmenté de 0.15f
        numProjectiles = 0;  // Réduit de 13
        spreadAngle = 1.2f;  // Réduit de 1.4f

        // Triple spirale (NERF : Moins de projectiles)
        if (spiralTimer >= 0.12f) {  // Augmenté de 0.1f
            static float spiralAngle = 0.0f;
            spiralAngle += 0.6f;  // Réduit de 0.8f

            // 3 spirales de 1 projectile = beaucoup d'espace
            for (int spiral = 0; spiral < 3; spiral++) {
                float angle = spiralAngle + (spiral * 3.14159f * 2 / 3);
                projectiles.push_back({
                    x + rect.w / 2,
                    y + rect.h / 2,
                    cos(angle) * (170.0f + spiral * 30.0f),  // Réduit
                    sin(angle) * (170.0f + spiral * 30.0f),
                    false,
                    {x + rect.w / 2 - 7, y + rect.h / 2 - 7, 14, 14}
                    });
            }
            spiralTimer = 0.0f;
        }

        // Cercles alternés (NERF : Moins de projectiles)
        if (specialAttackTimer >= 2.5f) {  // Augmenté de 2.0f
            static int alternatePattern = 0;
            alternatePattern = (alternatePattern + 1) % 2;

            // 12 projectiles max
            for (int i = 0; i < 12; i++) {
                float angle = (i / 12.0f) * 3.14159f * 2 + (alternatePattern * 0.22f);
                projectiles.push_back({
                    x + rect.w / 2,
                    y + rect.h / 2,
                    cos(angle) * 220.0f,  // Réduit de 250.0f
                    sin(angle) * 220.0f,
                    false,
                    {x + rect.w / 2 - 8, y + rect.h / 2 - 8, 16, 16}
                    });
            }
            specialAttackTimer = 0.0f;
        }

        // Pattern "pluie" (NERF : Plus d'espaces)
        if (waveTimer >= 2.0f) {  // Augmenté de 1.5f
            int numCols = 10;  // Réduit de 8
            float spacing = screenWidth / (numCols + 1.0f);

            static int offset = 0;
            offset = (offset + 1) % 2;

            for (int i = offset; i < numCols; i += 2) {
                float xPos = spacing * (i + 1);
                projectiles.push_back({
                    xPos,
                    y + rect.h / 2,
                    0.0f,
                    300.0f,  // Réduit de 350.0f
                    false,
                    {xPos - 10, y + rect.h / 2 - 10, 20, 20}
                    });
            }
            waveTimer = 0.0f;
        }
    }

    // Tir principal (NERF : Vitesse réduite)
    if (numProjectiles > 0 && shotTimer >= shotDelay) {
        for (int i = 0; i < numProjectiles; i++) {
            float angle = (i - (numProjectiles - 1) / 2.0f) * spreadAngle;
            projectiles.push_back({
                x + rect.w / 2,
                y + rect.h,
                sin(angle) * 80.0f,  // Réduit de 100.0f
                350.0f + (currentPhase * 40.0f),  // Réduit
                false,
                {x + rect.w / 2 - 4 + i * 8, y + rect.h, 8, 8}
                });
        }
        shotTimer = 0.0f;
    }

    // NOUVEAU : Logique de spawn pour Phantom et Sculk (seulement en phases avancées pour équilibrer)
    if (currentPhase >= 2 && phantomSpawnTimer >= 6.0f + rd.getRandomNumber(0, 200) / 100.0f) {  // Toutes les 6-8 secondes
        // Ici, tu dois ajouter le spawn dans ton game loop. Par exemple :
        // enemies.push_back(createEnemy(10, x + rd.getRandomNumber(-50, 50), y - 50, screenWidth, screenHeight));  // Phantom
        phantomSpawnTimer = 0.0f;
    }
    if (currentPhase >= 3 && sculkSpawnTimer >= 9.0f + rd.getRandomNumber(0, 200) / 100.0f) {  // Toutes les 9-11 secondes
        // enemies.push_back(createEnemy(11, x + rd.getRandomNumber(-50, 50), y - 50, screenWidth, screenHeight));  // Sculk
        sculkSpawnTimer = 0.0f;
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
    if (wardenHealthRef > 120) {
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    }
    else if (wardenHealthRef > 80) {
        SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
    }
    else if (wardenHealthRef > 40) {
        SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
    }
    else if (wardenHealthRef > 15) {
        SDL_SetRenderDrawColor(renderer, 200, 50, 0, 255);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
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