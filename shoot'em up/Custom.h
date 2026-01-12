#pragma once
#include <SDL3/SDL.h>
#include <string.h>
#include <stdbool.h>
#include <algorithm>
#include "Button.h"
#include "Label.h"
#include "TextBox.h"

class Custom
{
public:
    Custom(SDL_Window* window, TTF_Font* font);
    void handleEvent(const SDL_Event& event, bool& shouldSwitchToMenu);
    /*std::string getPlayerName() const;*/
    void update();
    void draw(SDL_Renderer* renderer);
private:
    TTF_Font* font;
    int windowHeight;
    int windowWidth;
    int buttonWidth;
    int buttonHeight;
    int buttonX;
    int buttonY;
    int textboxWidth;
    int textboxHeight;
    int textboxX;
    int textboxY;
    int titleY;
    Button button;
    TextBox textbox;
    Label titleLabel;
};