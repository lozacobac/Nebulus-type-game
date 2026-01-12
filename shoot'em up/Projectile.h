#pragma once
#include <SDL3/SDL.h>
struct Projectile
{
	float x; // Position X
	float y; // Position Y
	float vx; // Pixels par secondes sur X
	float vy; // Pixels par secondes sur Y
	bool isPlayer; // Si le projectile est celui du joueur ou non
	SDL_FRect rect;
	SDL_Texture* texture;

	Projectile(float x, float y, float vx, float vy, bool isPlayer, SDL_FRect rect, SDL_Texture* tex = nullptr);

	void update(float deltaTime); 
	bool isOffScreen(int w, int h);
};

