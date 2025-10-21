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

	int speedY = 2;
	std::vector<Bullet> Bullets;


	void MoveX(int value) {
		// X-Axis Input bounds
		if (value < 0) {
			rectangle->x = std::max(rectangle->x + (value * speedX), static_cast<float>(WIDTH / 4));
		}
		if (value > 0) {
			rectangle->x = std::min(rectangle->x + (value * speedX), static_cast<float>(WIDTH - (WIDTH / 4) - (rectangle->w)));
		}

	}

	void Shoot(SDL_Renderer* renderer) {

		// Add a bullet to bullet array
		Bullet newBullet("b", "source/assets/bullet.png", renderer, rectangle->x + rectangle->w / 2, rectangle->y - 100, 25, 100, 10);
		Bullets.push_back(newBullet);

	}

	// Happens every game loop
	virtual void Tick() override {


	}

};
