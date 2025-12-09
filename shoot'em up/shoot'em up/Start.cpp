#include "Start.h"

Start::Start()
{
    // Initialiser les boutons du menu (coordonnées pour 640x480)
    startButton = createButton(220, 200, 200, 50, "Start");
    leaveButton = createButton(220, 300, 200, 50, "Leave");
}

bool Start::initializeSDL()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Erreur lors de l'initialisation de SDL : %s", SDL_GetError());
        return false;
    }
    return true;
}

bool Start::CreateWindowAndRenderer(SDL_Window*& window, SDL_Renderer*& renderer)
{
    // Créer une fenêtre de 640x480
    if (!SDL_CreateWindowAndRenderer("AeroBlade SDL", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Erreur lors de la création de la fenêtre et du renderer : %s", SDL_GetError());
        return false;
    }
    
    // Configurer la présentation logique pour avoir un système de coordonnées fixes
    SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    
    return true;
}