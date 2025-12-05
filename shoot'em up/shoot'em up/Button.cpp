#include "Button.h"
#include <cstring> // Pour strlen

// Définition de createButton (inchangée)
Button createButton(float x, float y, float w, float h, const char* text) {
    Button btn;

    btn.rect.x = x;
    btn.rect.y = y;
    btn.rect.w = w;
    btn.rect.h = h;

    btn.text = text;

    btn.color.r = 70;
    btn.color.g = 130;
    btn.color.b = 180;
    btn.color.a = 255;

    btn.hoverColor.r = 100;
    btn.hoverColor.g = 149;
    btn.hoverColor.b = 237;
    btn.hoverColor.a = 255;

    btn.textColor.r = 255;
    btn.textColor.g = 255;
    btn.textColor.b = 255;
    btn.textColor.a = 255;

    btn.isHovered = false;
    btn.isPressed = false;
    btn.wasPressedOn = false;

    return btn;
}

// Définition de isPointInButton (inchangée)
bool isPointInButton(Button* btn, float x, float y) {
    return x >= btn->rect.x && x <= btn->rect.x + btn->rect.w &&
        y >= btn->rect.y && y <= btn->rect.y + btn->rect.h;
}

// Définition de handleButtonEvent (inchangée)
void handleButtonEvent(Button* btn, SDL_Event* e) {
    if (e->type == SDL_EVENT_MOUSE_MOTION) {
        float x = e->motion.x;
        float y = e->motion.y;
        btn->isHovered = isPointInButton(btn, x, y);
    }
    else if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN && e->button.button == SDL_BUTTON_LEFT) {
        float x = e->button.x;
        float y = e->button.y;
        if (isPointInButton(btn, x, y)) {
            btn->isPressed = true;
            btn->wasPressedOn = true; // la pression a commencé sur ce bouton
        }
    }
    else if (e->type == SDL_EVENT_MOUSE_BUTTON_UP && e->button.button == SDL_BUTTON_LEFT) {
        btn->isPressed = false;
    }
}

// Définition de isButtonClicked (inchangée)
bool isButtonClicked(Button* btn, SDL_Event* e) {
    if (e->type == SDL_EVENT_MOUSE_BUTTON_UP && e->button.button == SDL_BUTTON_LEFT) {
        float x = e->button.x;
        float y = e->button.y;

        // Clic valide seulement si pression et relâchement sur le même bouton
        if (btn->wasPressedOn && isPointInButton(btn, x, y)) {
            btn->wasPressedOn = false; // réinitialiser pour le prochain clic
            return true;
        }
        btn->wasPressedOn = false; // réinitialiser si relâchement en dehors
    }
    return false;
}

// Définition de renderButton (inchangée)
void renderButton(SDL_Renderer* renderer, Button* btn) {
    SDL_Color currentColor = btn->isHovered ? btn->hoverColor : btn->color;

    SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);
    SDL_RenderFillRect(renderer, &btn->rect);

    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    SDL_RenderRect(renderer, &btn->rect);

    const char* text = btn->text;
    int charWidth = 8, charHeight = 16;
    int textWidth = strlen(text) * charWidth;

    int textX = btn->rect.x + (btn->rect.w / 2) - (textWidth / 2);
    int textY = btn->rect.y + (btn->rect.h / 2) - (charHeight / 2);

    SDL_RenderDebugText(renderer, textX, textY, text);
}

// Nouvelle fonction : Gérer les événements pour tous les boutons
void handleAllButtons(Button* buttons, int numButtons, SDL_Event* e) {
    for (int i = 0; i < numButtons; ++i) {
        handleButtonEvent(&buttons[i], e);
        if (isButtonClicked(&buttons[i], e)) {
            SDL_Log("Bouton %d cliqué !", i + 1);
        }
    }
}

// Nouvelle fonction : Rendre tous les boutons
void renderAllButtons(SDL_Renderer* renderer, Button* buttons, int numButtons) {
    for (int i = 0; i < numButtons; ++i) {
        renderButton(renderer, &buttons[i]);
    }
}

// Nouvelle fonction : Boucle principale encapsulée
void runMainLoop(SDL_Renderer* renderer, Button* buttons, int numButtons) {
    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;
            handleAllButtons(buttons, numButtons, &e);
        }

        SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
        SDL_RenderClear(renderer);

        renderAllButtons(renderer, buttons, numButtons);

        SDL_RenderPresent(renderer);
    }
}