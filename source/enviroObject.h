#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/gameObject.h"
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/bullet.h"
#include <vector>


class EnviroObject : public GameObject {

	public:

	using GameObject::GameObject;

	// Happens every game loop
	virtual void Tick(float dt) override;

	bool CheckBounds();

};
