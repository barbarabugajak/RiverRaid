#pragma once
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include "../source/globals.h"
#include <cassert>


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
extern float worldSpeed = 250;
bool bShouldQuit = false;

void SetupWindowAndRenderer() {

	window = SDL_CreateWindow("RiverRaid", WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, NULL);

}

