#pragma once
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include "../source/globals.h"
#include <cassert>

SDL_Window* window = SDL_CreateWindow("RiverRaid", WIDTH, HEIGHT, 0);
SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
