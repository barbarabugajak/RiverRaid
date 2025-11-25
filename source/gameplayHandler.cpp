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
#include "../source/fuelBarrel.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_ttf/SDL_textengine.h>

void GameplayHandler::TogglePause() {
	bIsPaused = !bIsPaused;
}

void GameplayHandler::Quit() {
	bShouldQuit = true;
}

void GameplayHandler::GameOver(){
	bGameOver = true;
	Buttons.clear();
	SDL_ShowCursor();
	Buttons.emplace_back((WIDTH - 200.0f) / 2, HEIGHT / 2.f, 200.f, 60.f, &GameplayHandler::Quit, 0.5f, 0.f, 0.f, "Quit!");
	bShowUI = true;
}

void GameplayHandler::AddEnemy() {
	
	float enemyX = WIDTH / 6;
	enemyX += SDL_rand((Sint32)(WIDTH * (4.0f / 6.0f) - 110));
	Enemies.emplace_back("enemy", ENEMY_HELICOPTER_ASSET_SOURCE, renderer, enemyX, -50.f, 100.f, 75.f, 0.f, 300.f);
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

	const float x_min_o1 = o1.sprite.x;
	const float x_max_o1 = o1.sprite.x + o1.sprite.w;
	const float y_min_o1 = o1.sprite.y;
	const float y_max_o1 = o1.sprite.y + o1.sprite.h;


	const float x_min_o2 = o2.sprite.x;
	const float x_max_o2 = o2.sprite.x + o2.sprite.w;
	const float y_min_o2 = o2.sprite.y;
	const float y_max_o2 = o2.sprite.y + o2.sprite.h;


	return (
		x_min_o1 <= x_max_o2 &&
		x_max_o1 >= x_min_o2 &&
		y_min_o1 <= y_max_o2 &&
		y_max_o1 >= y_min_o2

		);
}

void GameplayHandler::Init() {

	// For memory efficiency
	Bullets.reserve(MAX_BULLET_AMOUNT);
	Buttons.reserve(2);
	Enemies.reserve(10);
	FuelBarrels.reserve(10);
	EnviroObjects.reserve(5);

	// Create and show UI
	Buttons.emplace_back((WIDTH - 200.0f) / 2, HEIGHT / 2.f - HEIGHT / 20.f, 200.f, 60.f, &GameplayHandler::TogglePause, 0.f, 0.7f, 0.f, "Play!");

	Buttons.emplace_back((WIDTH - 200.0f) / 2, HEIGHT / 2.f + HEIGHT / 20.f, 200.f, 60.f, &GameplayHandler::Quit, 0.5f, 0.f, 0.f, "Quit!");


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
			GameOver();
		}

		for (int j = (int)Bullets.size() - 1; j >= 0; j--) {

			if (CheckIfObjectsIntersect(Bullets[j], Enemies[i])) {
				Bullets.erase(Bullets.begin() + j);
				Enemies.erase(Enemies.begin() + i);

				bIsExploding = true;

				score += SCORE_FOR_ENEMY_DESTRUCTION + (int)(SCORE_FOR_ENEMY_DESTRUCTION*(worldSpeed/maxWorldSpeed));
				break;
			}

		}
	}

	for (int i = (int)FuelBarrels.size() - 1; i >= 0; i--) {

		if (CheckIfObjectsIntersect(player, FuelBarrels[i])) {

			GameOver();
			break;
		}

		for (int j = (int)Bullets.size() - 1; j >= 0; j--) {

			if (CheckIfObjectsIntersect(Bullets[j], FuelBarrels[i])) {

				bIsExploding = true;
				Bullets.erase(Bullets.begin() + j);
				FuelBarrels.erase(FuelBarrels.begin() + i);
				player.fuelCount = std::min(player.fuelCount + 50.0f, 99.99f);
				break;
			}


		}
	}
	
}

void GameplayHandler::SpawnExplosionSpecialEffect(float posX, float posY) {
}

void GameplayHandler::SpawnEnviroObject() {

	float posX;
	
	if (SDL_randf() < 0.5f) {
		posX = 0.f;
	} else {
		posX = WIDTH - 110;
	}
	
	Sint32 index = SDL_rand(6);

	EnviroObjects.emplace_back(EnviroObject("explosion",
		ENVIRO_ASSETS_SOURCES[(int)(index)],
		renderer,
		posX, (float)(index), 100, 100, 0, 0));
	EnviroObjects.back().velY = 1.f;
}

void GameplayHandler::UpdateFuel(float dt) {

	player.fuelCount -=  worldSpeed * dt * FUELL_LOSS_COEFFICIENT; 
	if (player.fuelCount <= 0.f) {
		GameOver();
	}
}

void GameplayHandler::UpdateFuelBarrels(float dt) {

	for (int i = (int)FuelBarrels.size() - 1; i >= 0; i--) {

		FuelBarrels[i].Tick(TARGET_FRAME_TIME);

		if (!FuelBarrels[i].CheckBounds()) {

			FuelBarrels.erase(FuelBarrels.begin() + i);

		}
	}

}

void GameplayHandler::UpdateOtherObjects(float dt) {

	for (int i = (int)EnviroObjects.size() - 1; i >= 0; i--) {

		EnviroObjects[i].Tick(TARGET_FRAME_TIME);

		if (!EnviroObjects[i].CheckBounds()) {

			EnviroObjects.erase(EnviroObjects.begin() + i);

		}
	}
}

void GameplayHandler::AddFuelBarrel() {
	float barrelX = WIDTH / 6;
	barrelX += SDL_rand((Sint32)(WIDTH * (4.0f / 6.0f) - 110));
	FuelBarrels.emplace_back("fuelBarrel", FUEL_BARREL_ASSET_SOURCE, renderer, barrelX, -50.f, 75.f, 100.f, 10.f, 300.f);
	FuelBarrels.back().velY = 1.f;
}

void GameplayHandler::Tick(float dt) {
	
	currentSpawnDelayValue -= (int)(dt * worldSpeed);
	if (currentSpawnDelayValue <= 0.f) {

		Sint32 rand = SDL_rand(100);

		if (rand <= FUEL_PROBABILITY || player.fuelCount < 20.f) {
			AddFuelBarrel();
		}
		else {
			AddEnemy();
		}

		rand = SDL_rand(100);

		if ((rand <= ENVIRO_PROBABILITY && EnviroObjects.size() < 4) || EnviroObjects.size() == 0) {
			SpawnEnviroObject();
		}

		currentSpawnDelayValue = spawnDelay;
	};

	if (!bGameOver) {
		player.Tick(dt);
		UpdateFuel(dt);
		CheckCollisions();
		
	}

	UpdateBullets(dt);
	UpdateFuelBarrels(dt);
	UpdateEnemies(dt);
	UpdateOtherObjects(dt);
	
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

	for (int i = 0; i < EnviroObjects.size(); i++) {
		EnviroObjects[i].Render(renderer);
	}

	for (int i = 0; i < FuelBarrels.size(); i++) {
		FuelBarrels[i].Render(renderer);
	}

	for (int i = 0; i < EnviroObjects.size(); i++) {
		EnviroObjects[i].Render(renderer);
	}

	if (!bGameOver) {
		player.Render(renderer);
	}
	
	scoreText.Render();
	fuelText.Render();
	

	if (bShowUI) {
		for (int i = 0; i < Buttons.size(); i++) {
			Buttons[i].Render();
		}
	}

}

