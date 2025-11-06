#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/bullet.h"
#include "../source/gameObject.h"
#include <vector>


class Plane : public GameObject {

	public:

		using GameObject::GameObject;
		std::vector<Bullet> Bullets;

		bool isShooting;
		float shootDelay = 0.0f;


	void MoveX(float dt) {
		// X-Axis Input bounds
		if (velX < 0) {
			sprite.x = std::max(sprite.x + (velX * speedX * dt), (WIDTH / 6.0f));
		}
		if (velX > 0) {
			sprite.x = std::min(sprite.x + (velX * speedX * dt), (WIDTH - (WIDTH / 6.0f) - (sprite.w)));
		}

	}

	void GetMovementInput() {

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

		if (key_states[SDL_SCANCODE_SPACE]) {
			isShooting = true;
		}
		else {
			isShooting = false;
		}
	}

	void Shoot(SDL_Renderer* renderer) {

		// Add a bullet to bullet array
		Bullets.emplace_back("b", "source/assets/bullet.png", renderer, sprite.x + sprite.w / 2.f, sprite.y - 50.f, 10.f, 50.f, 0.f, 1500.f);
		Bullets.back().velY = 1.f;
	}

	// Happens every game loop
	virtual void Tick(float dt) override {

		GetMovementInput();
		MoveX(dt);

		if (isShooting && shootDelay <= 0.f) {
			Shoot(renderer);
			shootDelay += 10.0f * dt;
		}
		
		if (shootDelay > 0.0f) shootDelay -=dt;
	}

};
