#include "Projectile.h"

Projectile::Projectile(float x, float y, float vx, float vy, bool isPlayer, SDL_FRect rect, SDL_Texture* tex)
    : x(x), y(y), vx(vx), vy(vy), isPlayer(isPlayer), rect(rect), texture(tex) {
}

// Base pour cr�er le projectile
void Projectile::update(float deltaTime) {
    x += vx * deltaTime;
    y += vy * deltaTime;
    rect.x = x;
    rect.y = y;
}

bool Projectile::isOffScreen(int w, int h) { // Supprime le projectile une fois qu'il a disparu de l'�cran
	return x<0 || x>w || y<0 || y>h;
}