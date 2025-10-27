#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>
#include <textures.h>
#include <cassert>

SDL_Texture* CreateTextureFromPNG(const char* path, SDL_Renderer* renderer) {

	SDL_Surface* surface = IMG_Load(path);

	if (!surface) return NULL;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_DestroySurface(surface);

	return texture;
}