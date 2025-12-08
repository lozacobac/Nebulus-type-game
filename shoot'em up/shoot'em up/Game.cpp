#include "Game.h"
#include <iostream>

void Game::handleMenuEvent(const SDL_Event& event, bool& startGame) {
    handleButtonEvent(&menuButton, const_cast<SDL_Event*>(&event));
    if (isButtonClicked(&menuButton, const_cast<SDL_Event*>(&event))) {
        startGame = true;
    }
}

void Game::drawMenu(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255);
    SDL_RenderFillRect(renderer, nullptr);
    renderButton(renderer, &menuButton);
}

void Game::loadLevel(int index) {
    if (index < 0 || index >= (int)levelsOrder.size()) return;
    currentLevel = std::make_unique<Level2>(levelsOrder[index]);
}

int Game::run() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) return 1;
    if (SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) != 0) return 1;

    menuButton = createButton(300, 250, 200, 50, "Start");

    // Charger l'ordre des niveaux depuis un fichier texte
    LevelLoader loader;
    int rows, cols;
    loader.load("levels_order.txt", levelsOrder, rows, cols);

    bool keepGoing = true;
    while (keepGoing) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) keepGoing = false;
            else if (currentState == State::MENU) {
                bool startGame = false;
                handleMenuEvent(event, startGame);
                if (startGame) {
                    currentLevelIndex = 0;
                    loadLevel(currentLevelIndex);
                    currentState = State::LEVEL;
                }
            }
            else if (currentState == State::LEVEL && currentLevel) {
                bool switchToMenu = false;
                currentLevel->handleEvent(event, switchToMenu);
                if (switchToMenu) currentState = State::MENU;
            }
        }

        float deltaTime = 1.0f / 60.0f;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (currentState == State::MENU) drawMenu(renderer);
        else if (currentState == State::LEVEL && currentLevel) {
            currentLevel->update(deltaTime);
            currentLevel->draw(renderer);

            if (currentLevel->isCompleted()) {
                currentLevelIndex++;
                if (currentLevelIndex < (int)levelsOrder.size())
                    loadLevel(currentLevelIndex);
                else
                    currentState = State::MENU;
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
