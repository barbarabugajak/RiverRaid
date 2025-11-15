#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/gameObject.h"
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/bullet.h"
#include <vector>

class GameplayHandler;

class Plane : public GameObject

{

public:

	using GameObject::GameObject;

	GameplayHandler* gameplayHandler;

	bool isShooting;
	float shootDelay = 0.0f;

	void MoveX(float dt);

	void GetMovementInput();

	void Shoot();

	virtual void Tick(float dt) override;

};