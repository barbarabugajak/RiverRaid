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
#include "../source/textObject.h"

class GameplayHandler {
public:
    Plane player;
    std::vector<Bullet> Bullets;
    std::vector<Enemy> Enemies;
    std::vector<GameObject> OtherObjects;

    const int enemySpawnDelayAmount = 250;
    int enemySpawnDelay = enemySpawnDelayAmount;
    int score = 1;
    TTF_Font* font;

    GameplayHandler()
        : player("plane", "source/assets/plane.png", renderer,
            0, 0, 100, 100, 150, 10) {

        player.velX = 0;
        player.sprite.x = (WIDTH / 2) - (player.sprite.w / 2);
        player.sprite.y = HEIGHT - 200;
        player.gameplayHandler = this;

        font = TTF_OpenFont("source/assets/arial.ttf", 24);
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
    void SpawnExplosionSpecialEffect(int posX, int posY);

    bool CheckIfObjectsIntersect(GameObject& o1, GameObject& o2);

};
