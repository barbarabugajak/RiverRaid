#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3/SDL.h>

void PrepareEnviro();
void DrawEnviro(SDL_Renderer* renderer);

// Enviro objects
extern SDL_FRect grass_L;
extern SDL_FRect grass_R;