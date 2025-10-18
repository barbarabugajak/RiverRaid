#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>

SDL_Texture* CreateTextureFromPNG(const char* path, SDL_Renderer* renderer);