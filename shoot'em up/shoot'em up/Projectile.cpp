#include "Projectile.h"

// Base pour créer le projectile
void Projectile::update(float deltaTime) {
	x += vx * deltaTime;
	y += vy * deltaTime;
	rect.x = x;
	rect.y = y;
}

bool Projectile::isOffScreen(int w, int h) { // Supprime le projectile une fois qu'il a disparu de l'écran
	return x<0 || x>w || y<0 || y>h;
}