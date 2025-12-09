#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include <vector>
#include <string>
#include "Button.h"
#include "Select.h"
#include "Custom.h"
#include "LevelBase.h"
#include "LevelLoader.h"

class Game
{
public:
    int run();

private:
    Select select;
    Custom custom;
    std::vector<std::string> levelsOrder;
    int currentLevelIndex;
    std::unique_ptr<LevelBase> currentLevel;

    enum class State { MENU, CUSTOM, SELECT, LEVEL };
    State currentState;

    Button menuButton;

    void loadLevel(int index);
    void handleMenuEvent(const SDL_Event& event, bool& shouldSwitchToCustom);
    void drawMenu(SDL_Renderer* renderer);

    bool initializeSDL();
    bool CreateWindowAndRenderer(SDL_Window*& window, SDL_Renderer*& renderer);
};