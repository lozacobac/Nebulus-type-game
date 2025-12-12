#include "Select.h"

Select::Select(SDL_Window* window) {
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    margin = 20;
    // Bouton 1 : Coin supérieur gauche
    button1Width = windowWidth * 0.45;
    button1Height = windowHeight*0.4;
    button1X = margin;
    button1Y = margin;
    buttonLevel1 = createButton(button1X, button1Y, button1Width, button1Height, "Level 1");

    // Bouton 2 : Coin supérieur droit
    button2Width = windowWidth * 0.45;
    button2Height = windowHeight * 0.4;
    button2X = windowWidth - button2Width - margin;
    button2Y = margin;
    buttonLevel2 = createButton(button2X, button2Y, button2Width, button2Height, "Level 2");

    // Bouton 3 : Coin inférieur gauche
    button3Width = windowWidth * 0.45;
    button3Height = windowHeight * 0.4;
    button3X = margin;
    button3Y = button1Height + margin * 2;
    buttonLevel3 = createButton(button3X, button3Y, button3Width, button3Height, "Level 3");

    // Bouton 4 : Coin inférieur droit
    button4Width = windowWidth * 0.45;
    button4Height = windowHeight * 0.4;
    button4X = windowWidth - button4Width - margin;
    button4Y = button2Height + margin*2;
    buttonLevel4 = createButton(button4X, button4Y, button4Width, button4Height, "Level 4");
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