#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/gameObject.h"
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/bullet.h"
#include "../source/plane.h"
#include "../source/gameplayHandler.h"
#include <vector>

void Plane::MoveX(float dt) {
		// X-Axis Input bounds
		if (velX < 0) {
			sprite.x = std::max(sprite.x + (velX * speedX * dt), (WIDTH / 6.0f));
		}
		if (velX > 0) {
			sprite.x = std::min(sprite.x + (velX * speedX * dt), (WIDTH - (WIDTH / 6.0f) - (sprite.w)));
		}

	}

void Plane::GetMovementInput() {

		const bool* key_states = SDL_GetKeyboardState(NULL);

		if (key_states[SDL_SCANCODE_D]) {
			velX = 1.0f;
		}

		if (key_states[SDL_SCANCODE_A]) {
			velX = -1.0f;
		}

		if (!(key_states[SDL_SCANCODE_A] || key_states[SDL_SCANCODE_D])) {
			velX = 0;
		}

		// They cancel out 
		if ((key_states[SDL_SCANCODE_A] && key_states[SDL_SCANCODE_D])) {
			velX = 0;
		}

		if (key_states[SDL_SCANCODE_W]) {
			worldSpeed = std::min((float)maxWorldSpeed, worldSpeed + speedY);
		}

		if (key_states[SDL_SCANCODE_S]) {
			worldSpeed = std::max((float)minWorldSpeed, worldSpeed - speedY);
		}

		if (!key_states[SDL_SCANCODE_W] && !key_states[SDL_SCANCODE_S]) {
			worldSpeed = std::max((float)minWorldSpeed, worldSpeed - speedY * 0.5f);
		}

		if (key_states[SDL_SCANCODE_SPACE]) {
			isShooting = true;
		}
		else {
			isShooting = false;
		}
	}

void Plane::Shoot() {

		// Add a bullet to bullet array
		gameplayHandler->Bullets.emplace_back("b", BULLET_ASSET_SOURCE, renderer, sprite.x + sprite.w / 2.f, sprite.y - 50.f, 10.f, 50.f, 0.f, 2000.f);
		gameplayHandler->Bullets.back().velY = 1.f;
	}

// Happens every game loop
void Plane::Tick(float dt) {

		GetMovementInput();
		MoveX(dt);

		if (isShooting && shootDelay <= 0.f) {
			Shoot();
			shootDelay += 15.0f * dt;
		}
		
		if (shootDelay > 0.0f) shootDelay -=dt;
	}

