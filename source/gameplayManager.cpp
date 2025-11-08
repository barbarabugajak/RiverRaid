#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/gameObject.h"
#include "../source/GameplayManager.h"


void GameplayManager::AddEnemies() {
	
	float enemyX = WIDTH / 6;
	enemyX += SDL_rand(WIDTH * (4.0f / 6.0f) - 110);
	Enemies.emplace_back(Enemy("enemy", "source/assets/helicopter.png", renderer, enemyX, -50, 100, 75, 0, 300));
	Enemies.back().velY = 1.f;

}

void GameplayManager::Tick(float dt) {

	enemySpawnDelay -= dt * worldSpeed;
	if (enemySpawnDelay <= 0.f) {
		enemySpawnDelay = enemySpawnDelayAmount;
		AddEnemies();
	}
}