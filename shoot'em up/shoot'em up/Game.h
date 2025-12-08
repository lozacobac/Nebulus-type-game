#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include <vector>
#include <string>

#include "Start.h"
#include "Select.h"
#include "Custom.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "LevelLoader.h"

class Game
{
public:
    int run();

private:
    Select select;
    Custom custom;

    std::vector<std::string> levelsOrder;
    int currentLevelIndex = 0;

    std::unique_ptr<LevelBase> currentLevel = nullptr;

    enum class State { MENU, CUSTOM, SELECT, LEVEL };
    State currentState = State::MENU;

    Button menuButton;

    void loadLevel(int index, SDL_Renderer* renderer);
    void handleMenuEvent(const SDL_Event& event, bool& shouldSwitchToCustom);
    void drawMenu(SDL_Renderer* renderer);
};
