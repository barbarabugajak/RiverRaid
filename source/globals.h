#pragma once

constexpr int WIDTH = 720;
constexpr int HEIGHT = 1080;

extern int worldSpeed;
constexpr int maxWorldSpeed = 500;
constexpr int minWorldSpeed = 200;
constexpr float TARGET_FRAME_TIME = 1.0f / 60.f;
extern bool bShouldQuit;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

void SetupWindowAndRenderer();
