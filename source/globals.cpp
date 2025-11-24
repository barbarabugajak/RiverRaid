#pragma once
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include "../source/globals.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <cassert>
#include <iostream>


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
extern float worldSpeed = 250;
extern bool bIsExploding = false;
bool bShouldQuit = false;
bool bIsPaused = true;


void SetupWindowAndRenderer() {

	window = SDL_CreateWindow("RiverRaid", WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, NULL);

}

const char* FONT_ASSET_SOURCE = "assets/graphic/arial.ttf";

void LoadFont() {

	font = TTF_OpenFont(FONT_ASSET_SOURCE, 24);

	if (!font) {
		printf("Couldn't open font: %s\n", SDL_GetError());
	} 

}

