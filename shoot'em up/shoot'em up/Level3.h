#pragma once
#include <SDL3/SDL.h>
#include "Button.h"

class Level3
{
public:
    Level3();
    void handleEvent(const SDL_Event& event, bool& shouldSwitchToMenu);
    void draw(SDL_Renderer* renderer);

private:
    Button button;
};