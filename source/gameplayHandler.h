#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_ttf/SDL_textengine.h>
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/gameObject.h"
#include "../source/Enemy.h"
#include "../source/plane.h"
#include "../source/button.h"
#include "../source/textObject.h"
#include "../source/fuelBarrel.h"
#include "../source/enviroObject.h"

class GameplayHandler {

public:

    // ===== ASSETS ========
    const char* PLANE_ASSET_SOURCE = "assets/graphic/plane.png";
    const char* ENEMY_HELICOPTER_ASSET_SOURCE = "assets/graphic/helicopter.png";
    const char* EXPLOSION_ASSETS_SOURCE = "assets/graphic/explosion.png";
    const char* FUEL_BARREL_ASSET_SOURCE = "assets/graphic/fuel.png";
    const char* ENVIRO_ASSETS_SOURCES[7] = {
        "assets/graphic/tree1.png",
        "assets/graphic/tree2.png",
        "assets/graphic/stone1.png",
        "assets/graphic/camp1.png",
        "assets/graphic/flowers1.png",
        "assets/graphic/flowers2.png",
        "assets/graphic/flowers3.png",
    };

    // ==== MEMBERS ========
    Plane player;
    std::vector<Bullet> Bullets;
    std::vector<Enemy> Enemies;
    std::vector<FuelBarrel> FuelBarrels;
    std::vector<EnviroObject> EnviroObjects;
    std::vector<Button> Buttons;
    TextObject<int> scoreText{ "Scosre: %d", WIDTH / 2.f, HEIGHT - 100, 150.0f, 50.f, 255, 255, 255, score };
    TextObject<float> fuelText{"Fuel: %.2f", WIDTH / 2.f, HEIGHT - 100, 150.0f, 50.f, 255, 255, 255, player.fuelCount };

    const int spawnDelay = 200;
    int currentSpawnDelayValue = spawnDelay;
    int score = 0;
 

    GameplayHandler()
        : player("plane", PLANE_ASSET_SOURCE, renderer,
            0, 0, 100, 100, 150, 100) {

        player.velX = 0;
        player.sprite.x = (WIDTH / 2) - (player.sprite.w / 2);
        player.sprite.y = HEIGHT - 200;
        player.gameplayHandler = this;
        scoreText.sprite.x = ((WIDTH - scoreText.sprite.w) / 2) - WIDTH / 6.f;
        fuelText.sprite.x = ((WIDTH - scoreText.sprite.w) / 2) + WIDTH / 6.f;

        if (!font) {
            SDL_Log("Couldn't open font: %s\n", SDL_GetError());
        }
    }

    void Init();
    void AddEnemy();
    void AddFuelBarrel();
    void Tick(float dt);
    void UpdateBullets(float dt);
    void UpdateEnemies(float dt);
    void UpdateOtherObjects(float dt);
    void UpdateFuelBarrels(float dt);
    void UpdateFuel(float dt);
    void Render();
    void CheckCollisions();
    void SpawnExplosionSpecialEffect(float posX, float posY);
    void SpawnEnviroObject();

    bool CheckIfObjectsIntersect(GameObject& o1, GameObject& o2);

    void CheckIfAnyButtonWasClicked();
    bool bShowUI = true;
    bool bGameOver = false;
    void GameOver();
    static void TogglePause();
    static void Quit();


};
