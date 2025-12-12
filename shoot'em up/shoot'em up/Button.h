#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <stdbool.h>

typedef struct {
    SDL_FRect rect;
    std::string text;
    SDL_Color color;
    SDL_Color hoverColor;
    SDL_Color textColor;
    bool isHovered;
    bool isPressed;
    bool wasPressedOn;
} Button;

Button createButton(float x, float y, float w, float h, const char* text);
bool isPointInButton(Button* btn, float x, float y);
void handleButtonEvent(Button* btn, SDL_Event* e);
bool isButtonClicked(Button* btn, SDL_Event* e);
void renderButton(SDL_Renderer* renderer, Button* btn);