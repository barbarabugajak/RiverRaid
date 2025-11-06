#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/gameObject.h"


class Bullet : public GameObject {

public:

	using GameObject::GameObject;
	
	void MoveY(float value) {
		// Y-Axis Input bounds
		sprite.y += value;
	}

	bool CheckBounds() {
		return ((sprite.y - sprite.h) < HEIGHT) && (sprite.y > 0.0f - sprite.h/2);
	}

	// Happens every game loop
	virtual void Tick(float dt) override {

		MoveY(-velY*speedY*dt);

	}

};
