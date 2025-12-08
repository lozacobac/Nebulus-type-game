#include "Level2.h"

Level2::Level2() : currentCommand(0), levelStartTime(0), levelCompleted(false), levelFailed(false) {
    button = createButton(220, 400, 200, 50, "Menu");
    script = loadScript("level2.txt");
    levelStartTime = SDL_GetTicks();
    std::cout << "Level2 initialisé. Script chargé avec " << script.size() << " commandes." << std::endl;
    if (script.empty()) {
        std::cout << "Avertissement : script vide. Ajout d'un ennemi par défaut pour test." << std::endl;
        // Ajout d'un ennemi par défaut si script vide
        enemies.push_back(createEnemy(1, 400, 100));
    }
}

std::vector<ScriptCommand> Level2::loadScript(const std::string& filename) {
    std::vector<ScriptCommand> scr;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty() && line[0] != '#') {
                ScriptCommand cmd;
                std::istringstream iss(line);
                iss >> cmd.time >> cmd.command;
                std::string param;
                while (iss >> param) cmd.params.push_back(param);
                scr.push_back(cmd);
            }
        }
        file.close();
        std::cout << "Script " << filename << " chargé avec " << scr.size() << " commandes." << std::endl;
    }
    else {
        std::cerr << "Erreur : impossible de charger " << filename << ". Assure-toi qu'il existe." << std::endl;
    }
    return scr;
}

void Level2::executeCommand(const ScriptCommand& cmd) {
    std::cout << "Exécution commande : " << cmd.command << " à temps " << cmd.time << std::endl;
    if (cmd.command == "SPAWN" && cmd.params.size() >= 4 && cmd.params[0] == "ENEMY") {
        float x = std::stof(cmd.params[1]), y = std::stof(cmd.params[2]);
        int type = std::stoi(cmd.params[3]);
        auto enemy = createEnemy(type, x, y);
        if (enemy) {
            enemies.push_back(std::move(enemy));
            std::cout << "Ennemi spawné à (" << x << ", " << y << ") type " << type << std::endl;
        }
    }
    else if (cmd.command == "END") {
        levelCompleted = true;
        std::cout << "Niveau terminé !" << std::endl;
    }
}

void Level2::handleCollisions() {
    allProjectiles = player.projectiles;
    for (auto& e : enemies) {
        for (auto& p : e->projectiles) allProjectiles.push_back(p);
    }

    for (auto pit = allProjectiles.begin(); pit != allProjectiles.end(); ) {
        bool hit = false;
        if (pit->isPlayer) {
            for (auto eit = enemies.begin(); eit != enemies.end(); ) {
                if ((*eit)->checkCollision(pit->rect)) {
                    eit = enemies.erase(eit);
                    hit = true;
                    std::cout << "Ennemi détruit !" << std::endl;
                    break;
                }
                else ++eit;
            }
        }
        else {
            if (player.checkCollision(pit->rect)) {
                player.lives--;
                hit = true;
                std::cout << "Joueur touché ! Vies restantes : " << player.lives << std::endl;
                if (player.lives <= 0) levelFailed = true;
            }
        }
        if (hit || pit->isOffScreen(800, 600)) pit = allProjectiles.erase(pit);
        else ++pit;
    }

    player.projectiles.clear();
    for (auto& p : allProjectiles) if (p.isPlayer) player.projectiles.push_back(p);
}

void Level2::handleEvent(const SDL_Event& event, bool& shouldSwitchToMenu) {
    handleButtonEvent(&button, const_cast<SDL_Event*>(&event));
    if (isButtonClicked(&button, const_cast<SDL_Event*>(&event))) {
        shouldSwitchToMenu = true;
    }
}

void Level2::update(float deltaTime) {
    const bool* keys = SDL_GetKeyboardState(NULL);
    player.update(keys, deltaTime);

    float elapsed = (SDL_GetTicks() - levelStartTime) / 1000.0f;
    while (currentCommand < script.size() && elapsed >= script[currentCommand].time) {
        executeCommand(script[currentCommand]);
        currentCommand++;
    }

    for (auto& e : enemies) e->update(deltaTime, player);
    handleCollisions();

    if (enemies.empty() && currentCommand >= script.size()) levelCompleted = true;
}

void Level2::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Fond noir
    SDL_RenderFillRect(renderer, nullptr);

    player.render(renderer);  // Joueur bleu
    for (auto& e : enemies) e->render(renderer);  // Ennemis rouges/orange

    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);  // Projectiles ennemis magenta
    for (auto& p : allProjectiles) if (!p.isPlayer) SDL_RenderFillRect(renderer, &p.rect);

    renderButton(renderer, &button);  // Bouton menu
}

bool Level2::isCompleted() const { return levelCompleted; }
bool Level2::isFailed() const { return levelFailed; }