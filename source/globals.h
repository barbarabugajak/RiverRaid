#pragma once

const int WIDTH = 720;
const int HEIGHT = 1080;

extern int worldSpeed;
const int maxWorldSpeed = 500;
const int minWorldSpeed = 200;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

void SetupWindowAndRenderer();
