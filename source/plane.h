#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/bullet.h"
#include "../source/gameObject.h"
#include <vector>


class Plane : public GameObject

{

public:

	using GameObject::GameObject;
	std::vector<Bullet> Bullets;

	bool isShooting;
	float shootDelay = 0.0f;
	static constexpr int MAX_BULLET_AMOUNT = 6;


	void MoveX(float dt);

	void GetMovementInput();

	void Shoot(SDL_Renderer* renderer);

	virtual void Tick(float dt) override;

};