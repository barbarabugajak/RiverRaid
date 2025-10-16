#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>

int main(int argc, char* argv[]) {

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


	// Create SDL window
	window = SDL_CreateWindow("RiverRaid", 1280, 1440, 0);

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

	bool close = false;
	float red = 0.1f, green = 0.5f, blue = 0.8f, alpha = 1.0f;

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

		// Draw onscreen
		SDL_RenderPresent(renderer);
	}


	// Shutdown
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return SDL_APP_SUCCESS;
}
