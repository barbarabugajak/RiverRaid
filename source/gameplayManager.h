#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/gameObject.h"
#include "../source/Enemy.h"


struct GameplayManager {

	std::vector<Enemy> Enemies;
	
	const int enemySpawnDelayAmount = 500.0f;
	int enemySpawnDelay = enemySpawnDelayAmount;;

	void AddEnemies();
	void Tick(float dt);

};
