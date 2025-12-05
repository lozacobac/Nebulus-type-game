#include <SDL3/SDL.h>
#include "Button.h"

int main(int argc, char* argv[]) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Erreur SDL_Init: %s", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Bouton SDL 3", 800, 600, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

	Button buttons[2] = {
		createButton(500, 250, 200, 100, "Cliquez-moi"),
		createButton(100, 250, 200, 100, "Bondoir")
	};

	runMainLoop(renderer, buttons, 2);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
