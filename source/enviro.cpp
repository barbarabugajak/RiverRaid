#include <enviro.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#include "../source/globals.h"

const char* texture_sources[3] = {
	"assets/graphic/tree1.png",
	"assets/graphic/tree2.png",
	"assets/graphic/stone1.png"
};

SDL_FRect grass_L;
SDL_FRect grass_R;

void PrepareEnviro() {

	// Prepare grass
	grass_L.x = 0;
	grass_L.y = 0;
	grass_L.w = WIDTH / 6;
	grass_L.h = HEIGHT;

	grass_R.x = WIDTH - WIDTH / 6;
	grass_R.y = 0;
	grass_R.w = WIDTH / 6;
	grass_R.h = HEIGHT;

}

void DrawEnviro() {

	SDL_SetRenderDrawColor(renderer, 0, 120, 0, 1);
	SDL_RenderFillRect(renderer, &grass_L);
	SDL_RenderFillRect(renderer, &grass_R);

}