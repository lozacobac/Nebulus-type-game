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
    Custom();
    void handleEvent(const SDL_Event& event, bool& shouldSwitchToSelect);
    void update();
    void draw(SDL_Renderer* renderer);

private:
    Button button;
    TextBox textbox;
    Label titleLabel;
};