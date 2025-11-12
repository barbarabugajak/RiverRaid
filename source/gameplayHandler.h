#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/gameObject.h"
#include "../source/Enemy.h"
#include "../source/plane.h"


class GameplayHandler {
public:
    Plane player;
    std::vector<Bullet> Bullets;
    std::vector<Enemy> Enemies;

    const int enemySpawnDelayAmount = 500;
    int enemySpawnDelay = enemySpawnDelayAmount;

    GameplayHandler()
        : player("plane", "source/assets/plane.png", renderer,
            0, 0, 100, 100, 300, 10) {

        player.velX = 0;
        player.sprite.x = (WIDTH / 2) - (player.sprite.w / 2);
        player.sprite.y = HEIGHT - 200;
        player.gameplayHandler = this;
    }

    void AddEnemies();
    void Tick(float dt);
    void UpdateBullets(float dt);
    void UpdateEnemies(float dt);
    void Render();
    void CheckCollisions();

    bool CheckIfObjectsIntersect(GameObject& o1, GameObject& o2);

};
