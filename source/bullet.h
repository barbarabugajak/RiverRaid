#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/gameObject.h"


class Bullet : public GameObject {

public:

	using GameObject::GameObject;

	int speedY = 2;


	void MoveY(int value) {
		// Y-Axis Input bounds
		rectangle->y += value * speedY;
	}

	bool CheckBounds() {
		return (rectangle->y < WIDTH) && (rectangle->y > 0.0f - rectangle->h/2);
	}

	// Happens every game loop
	virtual void Tick() override {

		MoveY(-1);

	}

};
