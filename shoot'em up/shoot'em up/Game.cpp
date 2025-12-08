#include "Game.h"

void Game::handleMenuEvent(const SDL_Event& event, bool& shouldSwitchToCustom) {
    handleButtonEvent(&menuButton, const_cast<SDL_Event*>(&event));
    if (isButtonClicked(&menuButton, const_cast<SDL_Event*>(&event))) {
        shouldSwitchToCustom = true;
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

    if (!initializeSDL()) {
        SDL_Quit();
        return 1;
    }

    if (!CreateWindowAndRenderer(window, renderer)) {
        SDL_Quit();
        return 1;
    }

    // Initialiser le bouton du menu
    menuButton = createButton(220, 200, 200, 50, "Start");

    SDL_StartTextInput(window);

    bool keepGoing = true;

    do {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                keepGoing = false;
            }
            else {
                if (currentState == State::MENU) {
                    bool shouldSwitch = false;
                    handleMenuEvent(event, shouldSwitch);
                    if (shouldSwitch) currentState = State::CUSTOM;
                }
                else if (currentState == State::CUSTOM) {
                    bool shouldSwitch = false;
                    custom.handleEvent(event, shouldSwitch);
                    if (shouldSwitch) currentState = State::SELECT;
                }
                else if (currentState == State::SELECT) {
                    int selectedLevel = 0;
                    select.handleEvent(event, selectedLevel);
                    if (selectedLevel == 1) currentState = State::LEVEL1;
                    else if (selectedLevel == 2) currentState = State::LEVEL2;
                    else if (selectedLevel == 3) currentState = State::LEVEL3;
                    else if (selectedLevel == 4) currentState = State::LEVEL4;
                }
                else if (currentState == State::LEVEL1) {
                    bool shouldSwitch = false;
                    level1.handleEvent(event, shouldSwitch);
                    if (shouldSwitch) currentState = State::MENU;
                }
                else if (currentState == State::LEVEL2) {
                    bool shouldSwitch = false;
                    level2.handleEvent(event, shouldSwitch);
                    if (shouldSwitch) currentState = State::MENU;
                }
                else if (currentState == State::LEVEL3) {
                    bool shouldSwitch = false;
                    level3.handleEvent(event, shouldSwitch);
                    if (shouldSwitch) currentState = State::MENU;
                }
                else if (currentState == State::LEVEL4) {
                    bool shouldSwitch = false;
                    level4.handleEvent(event, shouldSwitch);
                    if (shouldSwitch) currentState = State::MENU;
                }
            }
        }

        if (currentState == State::CUSTOM) {
            custom.update();
        }

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
        else if (currentState == State::LEVEL1) {
            level1.draw(renderer);
        }
        else if (currentState == State::LEVEL2) {
            level2.draw(renderer);
        }
        else if (currentState == State::LEVEL3) {
            level3.draw(renderer);
        }
        else if (currentState == State::LEVEL4) {
            level4.draw(renderer);
        }

        SDL_RenderPresent(renderer);
    } while (keepGoing);

    SDL_StopTextInput(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}