#include "Level2.h"

Level2::Level2() {
    button = createButton(220, 400, 200, 50, "Menu");
}

void Level2::handleEvent(const SDL_Event& event, bool& shouldSwitchToMenu) {
    handleButtonEvent(&button, const_cast<SDL_Event*>(&event));
    if (isButtonClicked(&button, const_cast<SDL_Event*>(&event))) {
        shouldSwitchToMenu = true;
    }
}

void Level2::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColorFloat(renderer, 0.0f, 1.0f, 0.0f, 1.0f);
    SDL_RenderFillRect(renderer, nullptr);

    renderButton(renderer, &button);
}