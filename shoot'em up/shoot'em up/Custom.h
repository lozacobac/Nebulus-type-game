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
    Custom(SDL_Window* window);
    void handleEvent(const SDL_Event& event, bool& shouldSwitchToSelect);
    void update();
    void draw(SDL_Renderer* renderer);
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
private:
    Button button;
    TextBox textbox;
    Label titleLabel;
};