#pragma once
#include <SDL3/SDL.h>
#include "Select.h"
#include "Custom.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Button.h"

class Game
{
public:
    int run();

private:
    Select select;
    Custom custom;
    Level1 level1;
    Level2 level2;
    Level3 level3;
    Level4 level4;

    enum class State { MENU, CUSTOM, SELECT, LEVEL1, LEVEL2, LEVEL3, LEVEL4 };
    State currentState = State::MENU;

    Button menuButton;

    void handleMenuEvent(const SDL_Event& event, bool& shouldSwitchToCustom);
    void drawMenu(SDL_Renderer* renderer);
};