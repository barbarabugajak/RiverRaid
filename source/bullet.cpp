#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/gameObject.h"
#include "../source/bullet.h"


bool Bullet::CheckBounds() {
	return ((sprite.y - sprite.h) < HEIGHT) && (sprite.y > 0.0f - sprite.h/2);
}

// Happens every game loop
void Bullet::Tick(float dt) {

	MoveY(-velY*speedY*dt);

}


