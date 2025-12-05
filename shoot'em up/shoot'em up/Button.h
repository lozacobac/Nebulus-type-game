#ifndef BUTTON_H
#define BUTTON_H

#include <SDL3/SDL.h>
#include <stdbool.h>

// Déclaration de la structure Button
typedef struct {
    SDL_FRect rect;
    const char* text;
    SDL_Color color;
    SDL_Color hoverColor;
    SDL_Color textColor;
    bool isHovered;
    bool isPressed;
    bool wasPressedOn; // variable pour savoir si la pression a commencé sur ce bouton
} Button;

// Prototypes des fonctions
Button createButton(float x, float y, float w, float h, const char* text);
bool isPointInButton(Button* btn, float x, float y);
void handleButtonEvent(Button* btn, SDL_Event* e);
bool isButtonClicked(Button* btn, SDL_Event* e);
void renderButton(SDL_Renderer* renderer, Button* btn);

// Nouvelles fonctions pour gérer plusieurs boutons
void handleAllButtons(Button* buttons, int numButtons, SDL_Event* e);
void renderAllButtons(SDL_Renderer* renderer, Button* buttons, int numButtons);
void runMainLoop(SDL_Renderer* renderer, Button* buttons, int numButtons);

#endif // BUTTON_H