#include "Custom.h"

Custom::Custom() {
    button = createButton(220, 200, 200, 50, "Continue");
}

void Custom::handleEvent(const SDL_Event& event, bool& shouldSwitchToSelect) {
    handleButtonEvent(&button, const_cast<SDL_Event*>(&event));
    if (isButtonClicked(&button, const_cast<SDL_Event*>(&event))) {
        shouldSwitchToSelect = true;
    }
}

void Custom::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColorFloat(renderer, 1.0f, 0.5f, 0.0f, 1.0f);
    SDL_RenderFillRect(renderer, nullptr);

    renderButton(renderer, &button);
}