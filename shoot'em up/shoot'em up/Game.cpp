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
    if (!SDL_CreateWindowAndRenderer("AeroBlade", 800, 600, 0, &window, &renderer)) {
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
    SDL_Event ev = event;
    handleButtonEvent(&menuButton, &ev);
    if (isButtonClicked(&menuButton, &ev)) {
        shouldSwitchToCustom = true;
    }
    if (isButtonClicked(&start.leaveButton, const_cast<SDL_Event*>(&event))) {
        shouldQuit = true;
    }
}

void Game::drawMenu(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColorFloat(renderer, 0.0f, 0.5f, 1.0f, 1.0f);
    SDL_RenderFillRect(renderer, nullptr);
    renderButton(renderer, &menuButton);
}

int Game::run() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_SetAppMetadata("AeroBlade", "1.0", "games.anakata.test-sdl");

    if (!start.initializeSDL()) {
        SDL_Quit();
        return 1;
    }

    if (!start.CreateWindowAndRenderer(window, renderer)) {
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

    menuButton = createButton(220.0f, 200.0f, 200.0f, 50.0f, "Start");
    SDL_StartTextInput(window);

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
            else {
                if (currentState == State::MENU) {
                    bool shouldSwitch = false;
                    handleMenuEvent(event, shouldSwitch);
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
        }

        // Update
        if (currentState == State::CUSTOM) {
            custom.update();
        }
        else if (currentState == State::LEVEL && currentLevel) {
            currentLevel->update(deltaTime);

            if (currentLevel->isCompleted()) {
                std::cout << "[INFO] Level completed!\n";
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
                std::cout << "[INFO] Level failed!\n";
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
