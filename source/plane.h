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
		int shootDelay = 0;


	void MoveX() {
		// X-Axis Input bounds
		if (velX < 0) {
			sprite->x = std::max(sprite->x + (velX * speedX), (WIDTH / 4.0f));
		}
		if (velX > 0) {
			sprite->x = std::min(sprite->x + (velX * speedX), (WIDTH - (WIDTH / 4.0f) - (sprite->w)));
		}

	}

	void Shoot(SDL_Renderer* renderer) {

		// Add a bullet to bullet array
		Bullets.push_back(Bullet("b", "source/assets/bullet.png", renderer, sprite->x + sprite->w / 2, sprite->y - 50, 10, 50, 0, 2));
	}

	// Happens every game loop
	virtual void Tick() override {
		MoveX();

		if (isShooting && shootDelay <= 0) {
			Shoot(renderer);
			shootDelay = 100;
		}

		// This'll work irregularily for now, due to time-frame differences
		// It's here so that State-Driven could be properly tested
		// TOFIX
		if (shootDelay > 0) shootDelay--;

	}

};
