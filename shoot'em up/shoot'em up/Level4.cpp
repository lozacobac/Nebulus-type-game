#include "Level4.h"

Level4::Level4() {
    button = createButton(220, 400, 200, 50, "Menu");
}

void Level4::handleEvent(const SDL_Event& event, bool& shouldSwitchToMenu) {
    handleButtonEvent(&button, const_cast<SDL_Event*>(&event));
    if (isButtonClicked(&button, const_cast<SDL_Event*>(&event))) {
        shouldSwitchToMenu = true;
    }
}

void Level4::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColorFloat(renderer, 0.5f, 0.0f, 0.5f, 1.0f);
    SDL_RenderFillRect(renderer, nullptr);

    renderButton(renderer, &button);
}