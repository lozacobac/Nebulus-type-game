#include "Select.h"

Select::Select(SDL_Window* window, TTF_Font* font) : font(font){
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    margin = 20;
    // Bouton 1 : Coin sup�rieur gauche
    button1Width = windowWidth * 0.45;
    button1Height = windowHeight*0.4;
    button1X = margin;
    button1Y = margin;
    buttonLevel1 = createButton(button1X, button1Y, button1Width, button1Height, "Level 1");

    // Bouton 2 : Coin sup�rieur droit
    button2Width = windowWidth * 0.45;
    button2Height = windowHeight * 0.4;
    button2X = windowWidth - button2Width - margin;
    button2Y = margin;
    buttonLevel2 = createButton(button2X, button2Y, button2Width, button2Height, "Level 2");

    // Bouton 3 : Coin inf�rieur gauche
    button3Width = windowWidth * 0.45;
    button3Height = windowHeight * 0.4;
    button3X = margin;
    button3Y = button1Height + margin * 2;
    buttonLevel3 = createButton(button3X, button3Y, button3Width, button3Height, "Level 3");

    // Bouton 4 : Coin inf�rieur droit
    button4Width = windowWidth * 0.45;
    button4Height = windowHeight * 0.4;
    button4X = windowWidth - button4Width - margin;
    button4Y = button2Height + margin*2;
    buttonLevel4 = createButton(button4X, button4Y, button4Width, button4Height, "Level 4");
}

void Select::handleEvent(const SDL_Event& event, int& selectedLevel) {
    if (inTransition) {
        // Gerer les evenements de l'ecran de transition
        handleButtonEvent(&buttonBackToMenu, const_cast<SDL_Event*>(&event));
        handleButtonEvent(&buttonNextWorld, const_cast<SDL_Event*>(&event));

        if (isButtonClicked(&buttonBackToMenu, const_cast<SDL_Event*>(&event))) {
            inTransition = false;
            selectedLevel = -1; // Code special pour retour au menu
        }
        else if (isButtonClicked(&buttonNextWorld, const_cast<SDL_Event*>(&event))) {
            inTransition = false;
            selectedLevel = 1 + currentWorld;
        }
    }

    else {
        // Gerer les evenements normaux de selection de niveau
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
}
void Select::draw(SDL_Renderer* renderer) {
    if (inTransition) {
        // Dessiner l'ecran de transition
        SDL_SetRenderDrawColorFloat(renderer, 0.2f, 0.2f, 0.3f, 1.0f);
        SDL_RenderFillRect(renderer, nullptr);

        // Pour l'instant, on dessine juste les boutons
        renderButton(renderer, &buttonBackToMenu, font);
        renderButton(renderer, &buttonNextWorld, font);
    }
    else {
        // Dessiner l'ecran de selection normal
        SDL_SetRenderDrawColorFloat(renderer, 1.0f, 1.0f, 0.0f, 1.0f);
        SDL_RenderFillRect(renderer, nullptr);

        renderButton(renderer, &buttonLevel1, font);
        renderButton(renderer, &buttonLevel2, font);
        renderButton(renderer, &buttonLevel3, font);
        renderButton(renderer, &buttonLevel4, font);
    }
}