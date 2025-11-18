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

class GameplayHandler {

public:

    // ===== ASSETS ========
    const char* PLANE_ASSET_SOURCE = "source/assets/plane.png";
    const char* ENEMY_HELICOPTER_ASSET_SOURCE = "source/assets/helicopter.png";
    const char* EXPLOSION_ASSETS_SOURCE = "source/assets/explosion.png";

    // ==== MEMBERS ========
    Plane player;
    std::vector<Bullet> Bullets;
    std::vector<Enemy> Enemies;
    std::vector<GameObject> OtherObjects;
    std::vector<Button> Buttons;
    TextObject<int> scoreText{ "Score: %d", WIDTH / 2.f, HEIGHT - 100, 150.0f, 50.f, 255, 255, 255, score };

    const int enemySpawnDelayAmount = 250;
    int enemySpawnDelay = enemySpawnDelayAmount;
    int score = 0;

    GameplayHandler()
        : player("plane", PLANE_ASSET_SOURCE, renderer,
            0, 0, 100, 100, 150, 10) {

        player.velX = 0;
        player.sprite.x = (WIDTH / 2) - (player.sprite.w / 2);
        player.sprite.y = HEIGHT - 200;
        player.gameplayHandler = this;
        scoreText.sprite.x = (WIDTH - scoreText.sprite.w) / 2;

        if (!font) {
            SDL_Log("Couldn't open font: %s\n", SDL_GetError());
        }
    }

    void Init();
    void AddEnemy();
    void Tick(float dt);
    void UpdateBullets(float dt);
    void UpdateEnemies(float dt);
    void Render();
    void CheckCollisions();
    void SpawnExplosionSpecialEffect(float posX, float posY);

    bool CheckIfObjectsIntersect(GameObject& o1, GameObject& o2);

    void CheckIfAnyButtonWasClicked();
    bool bShowUI = true;
    static void TogglePause();
    static void Quit();


};


namespace LetsHaveSomeFun {

}
