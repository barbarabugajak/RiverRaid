#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/enemy.h"
#include "../source/gameObject.h"
#include <vector>



// Happens every game loop
void Enemy::Tick(float dt) {
	MoveY(velY * worldSpeed * dt);
}

bool Enemy::CheckBounds() {
	return (sprite.y < HEIGHT);
}
