#pragma once
#include <SDL3/SDL.h>
#include "Button.h"

class Custom
{
public:
    Custom();
    void handleEvent(const SDL_Event& event, bool& shouldSwitchToSelect);
    void draw(SDL_Renderer* renderer);

private:
    Button button;
};