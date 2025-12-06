#pragma once
#include <SDL3/SDL.h>
#include "Button.h"

class Select
{
public:
    Select();
    void handleEvent(const SDL_Event& event, int& selectedLevel);
    void draw(SDL_Renderer* renderer);

private:
    Button buttonLevel1;
    Button buttonLevel2;
    Button buttonLevel3;
    Button buttonLevel4;
};