#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/gameObject.h"
#include "../source/GameplayHandler.h"
#include "../source/enviro.h"
#include "../source/button.h"
#include "../source/textObject.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_ttf/SDL_textengine.h>

void GameplayHandler::TogglePause() {
	bIsPaused = !bIsPaused;
}

void GameplayHandler::Quit() {
	bShouldQuit = true;
}

void GameplayHandler::AddEnemy() {
	
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

bool GameplayHandler::CheckIfObjectsIntersect(GameObject& o1, GameObject& o2) {

	float x_min_o1 = o1.sprite.x;
	float x_max_o1 = o1.sprite.x + o1.sprite.w;
	float y_min_o1 = o1.sprite.y;
	float y_max_o1 = o1.sprite.y + o1.sprite.h;


	float x_min_o2 = o2.sprite.x;
	float x_max_o2 = o2.sprite.x + o2.sprite.w;
	float y_min_o2 = o2.sprite.y;
	float y_max_o2 = o2.sprite.y + o2.sprite.h;


	return (
		x_min_o1 <= x_max_o2 &&
		x_max_o1 >= x_min_o2 &&
		y_min_o1 <= y_max_o2 &&
		y_max_o1 >= y_min_o2

		);
}

void GameplayHandler::Init() {
	// First initial wave
	AddEnemy();

	// For memory efficiency
	Bullets.reserve(MAX_BULLET_AMOUNT);
	Buttons.reserve(2);
	Enemies.reserve(10);

	// Create and show UI
	Buttons.emplace_back((WIDTH - 200.0f) / 2, HEIGHT / 2.f + HEIGHT / 20.f, 200.f, 60.f, &GameplayHandler::TogglePause, 0.f, 0.7f, 0.f, "Play!");

	Buttons.emplace_back(Button((WIDTH - 200.0f) / 2, HEIGHT / 2.f - HEIGHT / 20.f, 200.f, 60.f, &GameplayHandler::Quit, 0.5f, 0.f, 0.f, "Quit!"));


}

void GameplayHandler::CheckIfAnyButtonWasClicked() {
	for (int i = 0; i < Buttons.size(); i++) {
		if (Buttons[i].CheckHover()) {
			bShowUI = false;
		}
	}
}

void GameplayHandler::CheckCollisions() {

	for (int i = (int)Enemies.size() - 1; i >= 0; i--) {

		if (CheckIfObjectsIntersect(player, Enemies[i])) {
			std::cout << "Player crashes into enemy " << Enemies[i].name << std::endl;
			bShouldQuit = true;
		}

		for (int j = (int)Bullets.size() - 1; j >= 0; j--) {

			if (CheckIfObjectsIntersect(Bullets[j], Enemies[i])) {
				std::cout << "Enemy destroyed " << Enemies[i].name << std::endl;
				Bullets.erase(Bullets.begin() + j);
				Enemies.erase(Enemies.begin() + i);
				score += 10;
				break;
			}

		}
	}

}

void GameplayHandler::SpawnExplosionSpecialEffect(int posX, int posY) {

	OtherObjects.emplace_back(GameObject(
		"explosion",
		"source/assets/explosion.png",
		renderer,
		posX, posY, 100, 50, 0, 0));

	std::cout << "Boom" << std::endl;

}

void GameplayHandler::Tick(float dt) {
	
	enemySpawnDelay -= dt * worldSpeed;
	if (enemySpawnDelay <= 0.f) {
		enemySpawnDelay = enemySpawnDelayAmount;
		AddEnemy();
	};
	player.Tick(dt);

	UpdateEnemies(dt);
	UpdateBullets(dt);
	CheckCollisions();
	
	
}



void GameplayHandler::Render() {

	DrawEnviro();

	// Render bullets
	for (int i = 0; i < Bullets.size(); i++) {
		Bullets[i].Render(renderer);
	}

	// Render enemies
	for (int i = 0; i < Enemies.size(); i++) {
		Enemies[i].Render(renderer);
	}

	for (int i = 0; i < OtherObjects.size(); i++) {
		OtherObjects[i].Render(renderer);
	}

	player.Render(renderer);

	scoreText.Render();

	if (bShowUI) {
		for (int i = 0; i < Buttons.size(); i++) {
			Buttons[i].Render();
		}
	}

}

