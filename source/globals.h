#pragma once
#include <SDL3_ttf/SDL_ttf.h>

constexpr int WIDTH = 720;
constexpr int HEIGHT = 1080;

extern float worldSpeed;
constexpr float maxWorldSpeed = 600;
constexpr float minWorldSpeed = 250;
constexpr float TARGET_FRAME_TIME = 1.0f / 60.f;
extern bool bShouldQuit;
extern bool bIsPaused;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

void SetupWindowAndRenderer();

extern TTF_Font* font;
void LoadFont();
