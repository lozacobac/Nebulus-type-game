#include "Game.h"
#include <iostream>

bool Game::initializeSDL() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "[ERROR] SDL_Init failed: " << SDL_GetError() << "\n";
        return false;
    }
    return true;
}

bool Game::CreateWindowAndRenderer(SDL_Window*& window, SDL_Renderer*& renderer) {
    if (!SDL_CreateWindowAndRenderer("AeroBlade", 960, 540, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        std::cerr << "[ERROR] SDL_CreateWindowAndRenderer failed: " << SDL_GetError() << "\n";
        return false;
    }
    return true;
}

void Game::loadLevel(int index) {
    if (index < 0 || index >= (int)levelsOrder.size()) {
        std::cerr << "[ERROR] Invalid level index: " << index << "\n";
        return;
    }

    currentLevel = std::make_unique<LevelBase>();
    if (!currentLevel->loadFromFile(levelsOrder[index])) {
        std::cerr << "[ERROR] Failed to load level: " << levelsOrder[index] << "\n";
        currentLevel = nullptr;
    }
    else {
        std::cout << "[INFO] Level loaded: " << levelsOrder[index] << "\n";
    }
}

void Game::handleMenuEvent(const SDL_Event& event, bool& shouldSwitchToCustom) {
    // Debug : afficher la position de la souris
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        std::cout << "[DEBUG] Mouse click at: " << event.button.x << ", " << event.button.y << "\n";
        std::cout << "[DEBUG] Start button: x=" << start.startButton.rect.x
            << " y=" << start.startButton.rect.y
            << " w=" << start.startButton.rect.w
            << " h=" << start.startButton.rect.h << "\n";
        std::cout << "[DEBUG] Leave button: x=" << start.leaveButton.rect.x
            << " y=" << start.leaveButton.rect.y
            << " w=" << start.leaveButton.rect.w
            << " h=" << start.leaveButton.rect.h << "\n";
    }

    SDL_Event ev = event;

    // Gérer les événements de survol et de clic
    handleButtonEvent(&start.startButton, &ev);
    handleButtonEvent(&start.leaveButton, &ev);

    // Vérifier si le bouton Start est cliqué
    if (isButtonClicked(&start.startButton, &ev)) {
        std::cout << "[INFO] Start button clicked!\n";
        shouldSwitchToCustom = true;
    }

    // Vérifier si le bouton Leave est cliqué
    if (isButtonClicked(&start.leaveButton, &ev)) {
        std::cout << "[INFO] Leave button clicked!\n";
        shouldQuit = true;
    }
}

void Game::drawMenu(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColorFloat(renderer, 0.0f, 0.5f, 1.0f, 1.0f);
    SDL_RenderClear(renderer);

    renderButton(renderer, &start.startButton);
    renderButton(renderer, &start.leaveButton);
}

int Game::run() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_SetAppMetadata("AeroBlade", "1.0", "games.anakata.test-sdl");

    if (!start.initializeSDL()) {
        SDL_Quit();
        return 1;
    }

    if (!CreateWindowAndRenderer(window, renderer)) {
        SDL_Quit();
        return 1;
    }

    // Charger l'ordre des niveaux
    if (!LevelLoader::loadLevelsOrder("Levels_order.txt", levelsOrder)) {
        std::cerr << "[ERROR] Failed to load levels order\n";
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool keepGoing = true;
    Uint64 lastTime = SDL_GetTicks();
    currentLevelIndex = 0;
    currentState = State::MENU;

    do {
        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                keepGoing = false;
            }

            if (currentState == State::MENU) {
                // Traiter TOUS les événements pour le menu
                bool shouldSwitch = false;
                handleMenuEvent(event, shouldSwitch);

                // Vérifier si on doit quitter
                if (shouldQuit) {
                    keepGoing = false;
                }

                if (shouldSwitch) {
                    currentState = State::CUSTOM;
                }
            }
            else if (currentState == State::CUSTOM) {
                bool shouldSwitch = false;
                custom.handleEvent(event, shouldSwitch);
                if (shouldSwitch) {
                    currentState = State::SELECT;
                }
            }
            else if (currentState == State::SELECT) {
                int selectedLevel = 0;
                select.handleEvent(event, selectedLevel);
                if (selectedLevel >= 1 && selectedLevel <= (int)levelsOrder.size()) {
                    currentLevelIndex = selectedLevel - 1;
                    loadLevel(currentLevelIndex);
                    if (currentLevel) {
                        currentState = State::LEVEL;
                    }
                }
            }
            else if (currentState == State::LEVEL && currentLevel) {
                bool shouldSwitch = false;
                currentLevel->handleEvent(event, shouldSwitch);
                if (shouldSwitch) {
                    currentLevel = nullptr;
                    currentState = State::MENU;
                }
            }
        }

        // Update
        if (currentState == State::CUSTOM) {
            custom.update();
        }
        else if (currentState == State::LEVEL && currentLevel) {
            currentLevel->update(deltaTime);

            if (currentLevel->isCompleted()) {
                int levelScore = currentLevel->getScore();
                totalScore += levelScore;
                std::cout << "[INFO] Level completed! Score earned : " << levelScore << "| Total = " << totalScore << "\n";
                currentLevelIndex++;
                if (currentLevelIndex < (int)levelsOrder.size()) {
                    loadLevel(currentLevelIndex);
                }
                else {
                    std::cout << "[INFO] All levels completed!\n";
                    currentLevel = nullptr;
                    currentState = State::MENU;
                }
            }
            else if (currentLevel->isFailed()) {
                std::cout << "[INFO] Level failed!\n" << "[INFO] Score for this run : " << totalScore << "\n";
                totalScore = 0;
                currentLevel = nullptr;
                currentState = State::MENU;
            }
        }

        // Draw
        SDL_SetRenderDrawColorFloat(renderer, 0.0f, 0.0f, 0.0f, 1.0f);
        SDL_RenderClear(renderer);

        if (currentState == State::MENU) {
            drawMenu(renderer);
        }
        else if (currentState == State::CUSTOM) {
            custom.draw(renderer);
        }
        else if (currentState == State::SELECT) {
            select.draw(renderer);
        }
        else if (currentState == State::LEVEL && currentLevel) {
            currentLevel->draw(renderer);
        }

        SDL_RenderPresent(renderer);
    } while (keepGoing);

    SDL_StopTextInput(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
