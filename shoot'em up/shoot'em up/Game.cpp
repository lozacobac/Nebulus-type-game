#include "Game.h"

int Game::run() {
	SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_SetAppMetadata("AeroBlade", "1.0", "games.anakata.test-sdl");
    if (!SDL_Init(SDL_INIT_VIDEO))
        return 1;

    if (!SDL_CreateWindowAndRenderer("AeroBlade SDL", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer))
        return 1;

    SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    bool keepGoing = true;
    do
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                keepGoing = false;
        }

        const double now = ((double)SDL_GetTicks()) / 1000.0;
        SDL_SetRenderDrawColorFloat(renderer, 1.0f, 1.0f, 1.0f, 1.0f);

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    } while (keepGoing);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}