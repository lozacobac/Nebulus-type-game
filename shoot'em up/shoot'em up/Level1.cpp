#include "Level1.h"

Level1::Level1() {
    button = createButton(220, 400, 200, 50, "Menu");
}

void Level1::handleEvent(const SDL_Event& event, bool& shouldSwitchToMenu) {
    handleButtonEvent(&button, const_cast<SDL_Event*>(&event));
    if (isButtonClicked(&button, const_cast<SDL_Event*>(&event))) {
        shouldSwitchToMenu = true;
    }
}

void Level1::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColorFloat(renderer, 1.0f, 0.0f, 0.0f, 1.0f);
    SDL_RenderFillRect(renderer, nullptr);

    renderButton(renderer, &button);
}