#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/gameObject.h"
#include "../source/GameplayHandler.h"
#include "../source/enviro.h"


void GameplayHandler::AddEnemies() {
	
	float enemyX = WIDTH / 6;
	enemyX += SDL_rand(WIDTH * (4.0f / 6.0f) - 110);
	Enemies.emplace_back(Enemy("enemy", "source/assets/helicopter.png", renderer, enemyX, -50, 100, 75, 0, 300));
	Enemies.back().velY = 1.f;

}

void GameplayHandler::UpdateBullets(float dt) {

	for (int i = (int)Bullets.size() - 1; i >= 0; i--) {

		Bullets[i].Tick(TARGET_FRAME_TIME);

		if (!Bullets[i].CheckBounds()) {

			Bullets.erase(Bullets.begin() + i);

		}
	}
}


void GameplayHandler::UpdateEnemies(float dt) {

	for (int i = (int)Enemies.size() - 1; i >= 0; i--) {

		Enemies[i].Tick(TARGET_FRAME_TIME);

		if (!Enemies[i].CheckBounds()) {

			Enemies.erase(Enemies.begin() + i);

		}
	}

}
void GameplayHandler::Tick(float dt) {

	enemySpawnDelay -= dt * worldSpeed;
	if (enemySpawnDelay <= 0.f) {
		enemySpawnDelay = enemySpawnDelayAmount;
		AddEnemies();
	};
	player.Tick(dt);

	UpdateEnemies(dt);
	UpdateBullets(dt);

}

void GameplayHandler::Render() {

	// Render bullets
	for (int i = 0; i < Bullets.size(); i++) {
		Bullets[i].Render(renderer);
	}

	// Render enemies
	for (int i = 0; i < Enemies.size(); i++) {
		Enemies[i].Render(renderer);
	}

	player.Render(renderer);

	DrawEnviro();
}