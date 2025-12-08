#include "Custom.h"

Custom::Custom()
    : button(createButton(220, 200, 200, 50, "Continue"))// x , y , h , w , text
    , titleLabel(30, 50, "Entrez votre nom:", 1.5f)
    , textbox(30, 75, 400, 40, 32)
{
    titleLabel.setColor(255, 255, 255);  // Blanc
}

void Custom::handleEvent(const SDL_Event& event, bool& shouldSwitchToSelect) {
    handleButtonEvent(&button, const_cast<SDL_Event*>(&event));
    if (isButtonClicked(&button, const_cast<SDL_Event*>(&event))) {
        shouldSwitchToSelect = true;
    }

    textbox.handleEvent(event);
}

void Custom::update() {
    textbox.update();
}

void Custom::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColorFloat(renderer, 1.0f, 0.5f, 0.0f, 1.0f);
    SDL_RenderFillRect(renderer, nullptr);

    titleLabel.render(renderer);
    textbox.render(renderer);

    renderButton(renderer, &button);
}