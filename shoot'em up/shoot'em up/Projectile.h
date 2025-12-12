#pragma once
#include <SDL3/SDL.h>
struct Projectile
{
	float x;
	float y;
	float vx;
	float vy;
	bool isPlayer;
	SDL_FRect rect;

	void update(float deltaTime);
	bool isOffScreen(int w, int h);
};

