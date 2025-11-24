#pragma once
#include <SDL3_ttf/SDL_ttf.h>

constexpr int WIDTH = 720;
constexpr int HEIGHT = 1080;

extern float worldSpeed;
constexpr float maxWorldSpeed = 600;
constexpr float minWorldSpeed = 300;

constexpr int SCORE_FOR_ENEMY_DESTRUCTION = 10;

constexpr float FUELL_LOSS_COEFFICIENT = 0.01f;
constexpr int FUEL_PROBABILITY = 10;
constexpr int ENVIRO_PROBABILITY = 30;

constexpr float TARGET_FRAME_TIME = 1.0f / 60.f;

static constexpr size_t MAX_BULLET_AMOUNT = 6;

extern bool bShouldQuit;
extern bool bIsPaused;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

void SetupWindowAndRenderer();

extern TTF_Font* font;
void LoadFont();

extern bool bIsExploding;