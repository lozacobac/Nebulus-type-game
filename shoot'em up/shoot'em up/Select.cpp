#include "Select.h"

Select::Select() {
    buttonLevel1 = createButton(100, 100, 150, 50, "Level 1");
    buttonLevel2 = createButton(390, 100, 150, 50, "Level 2");
    buttonLevel3 = createButton(100, 330, 150, 50, "Level 3");
    buttonLevel4 = createButton(390, 330, 150, 50, "Level 4");
}

void Select::handleEvent(const SDL_Event& event, int& selectedLevel) {
    handleButtonEvent(&buttonLevel1, const_cast<SDL_Event*>(&event));
    handleButtonEvent(&buttonLevel2, const_cast<SDL_Event*>(&event));
    handleButtonEvent(&buttonLevel3, const_cast<SDL_Event*>(&event));
    handleButtonEvent(&buttonLevel4, const_cast<SDL_Event*>(&event));

    if (isButtonClicked(&buttonLevel1, const_cast<SDL_Event*>(&event))) {
        selectedLevel = 1;
    }
    else if (isButtonClicked(&buttonLevel2, const_cast<SDL_Event*>(&event))) {
        selectedLevel = 2;
    }
    else if (isButtonClicked(&buttonLevel3, const_cast<SDL_Event*>(&event))) {
        selectedLevel = 3;
    }
    else if (isButtonClicked(&buttonLevel4, const_cast<SDL_Event*>(&event))) {
        selectedLevel = 4;
    }
}

void Select::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColorFloat(renderer, 1.0f, 1.0f, 0.0f, 1.0f);
    SDL_RenderFillRect(renderer, nullptr);

    renderButton(renderer, &buttonLevel1);
    renderButton(renderer, &buttonLevel2);
    renderButton(renderer, &buttonLevel3);
    renderButton(renderer, &buttonLevel4);
}