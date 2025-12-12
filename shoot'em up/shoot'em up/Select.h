#pragma once
#include <SDL3/SDL.h>
#include "Button.h"

class Select
{
public:
    Select(SDL_Window* window);
    int margin;
    int windowHeight;
    int windowWidth;
    int button1Width;
    int button1Height;
    int button1X;
    int button1Y;
    int button2Width;
    int button2Height;
    int button2X;
    int button2Y;
    int button3Width;
    int button3Height;
    int button3X;
    int button3Y;
    int button4Width;
    int button4Height;
    int button4X;
    int button4Y;
    void handleEvent(const SDL_Event& event, int& selectedLevel);
    void draw(SDL_Renderer* renderer);

private:
    Button buttonLevel1;
    Button buttonLevel2;
    Button buttonLevel3;
    Button buttonLevel4;
};