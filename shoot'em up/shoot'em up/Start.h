#pragma once
#include <SDL3/SDL.h>

//Fonction pour initialiser SDL
bool initializeSDL();

//Fonction pour créer la fenêtre et le renderer
bool CreateWindowAndRenderer(SDL_Window*& window, SDL_Renderer*& renderer);

