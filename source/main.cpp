// SDL
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
// Project headers
#include "../textures.h"
// Generic
#include <iostream>

int main(int argc, char* argv[]) {

	const int WIDTH = 1280;
	const int HEIGHT = 1440;

	// Initalize video subsystem
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "Video did not initialize properly" << "\n";
		std::cout << SDL_GetError() << "\n";
		return SDL_APP_FAILURE;
	}
	else {
		std::cout << "Video initialized" << "\n";
	};


	// Declare variables for window and renderer
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	SDL_FRect r;

	r.w = 200;
	r.h = 200;

	r.x = (WIDTH /2) - (r.w/2);
	r.y = HEIGHT - 400;


	// Create SDL window
	window = SDL_CreateWindow("RiverRaid", WIDTH, HEIGHT, 0);

	if (!window) {
		std::cout << "Window creation error" << "\n";
		std::cout << SDL_GetError() << "\n";
		return SDL_APP_FAILURE;
	}
	else {
		std::cout << "Window created successfully" << "\n";;
	}

	// Create SDL renderer
	renderer = SDL_CreateRenderer(window, NULL);

	if (!renderer) {
		std::cout << SDL_GetError() << "\n";
		return SDL_APP_FAILURE;
	}
	else {
		std::cout << "Renderer created successfully" << "\n";;
	}

	SDL_Texture* plane = CreateTextureFromPNG("source/assets/plane.png", renderer);

	bool close = false;
	float red = 0.0f, green = 0.1f, blue = 0.7f, alpha = 1.0f;

	// Game loop
	while (!close) {

		SDL_Event event;

		// Event handler
		while (SDL_PollEvent(&event) ) {

			// Quit event handler
			if (event.type == SDL_EVENT_QUIT) {
				close = true;
				break;
			}

			
		}


		// Set backround color
		SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

		// Clear screen
		SDL_RenderClear(renderer); 

		SDL_SetRenderDrawColor(renderer, 1, 1, 1, 1);
		SDL_RenderTexture(renderer, plane, NULL, &r);
		
		

		// Draw onscreen
		SDL_RenderPresent(renderer);


	}


	// Shutdown
	SDL_DestroyTexture(plane);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return SDL_APP_SUCCESS;
}
