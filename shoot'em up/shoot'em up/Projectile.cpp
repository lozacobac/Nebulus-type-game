#include "Projectile.h"

void Projectile::update(float deltaTime) {
	x += vx * deltaTime;
	y += vy * deltaTime;
	rect.x = x;
	rect.y = y;
}

bool Projectile::isOffScreen(int w, int h) {
	return x<0 || x>w || y<0 || y>h;
}