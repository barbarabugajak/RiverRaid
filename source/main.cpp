// SDL
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_keycode.h>
// Project headers
#include "../source/textures.h"
#include "../source/gameObject.h"
#include "../source/enviro.h"
#include "../source/globals.h"
#include "../source/bullet.h"
#include "../source/plane.h"

// Generic
#include <iostream>
#include <vector>

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
	assert(window);
	assert(renderer);
	
	Plane plane("plane", "source/assets/plane.png", renderer, 0, 0, 100, 100, 1, 0);
	plane.velX = 0;
	plane.sprite->x = (WIDTH / 2) - (plane.sprite->w / 2);
	plane.sprite->y = HEIGHT - 200;

	bool close = false;
	float red = 0.0f, green = 0.1f, blue = 0.7f, alpha = 1.0f;

	// Initialize enviro
	PrepareEnviro();

	// Tick handlers
	unsigned int lastTickTime = 0, currentTime;

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
			

			if (event.type == SDL_EVENT_KEY_DOWN) {

				switch (event.key.key) {
					case SDLK_SPACE:
						plane.isShooting = true;
						break;
					case SDLK_D:
						plane.velX = 1;
						break;
					case SDLK_A:
						plane.velX = -1;
						break;
				}
				
			}

			if (event.type == SDL_EVENT_KEY_UP) {

				switch (event.key.key) {
					case SDLK_SPACE:
						plane.isShooting = false;
						break;
					case SDLK_D:
						plane.velX = 0;
						break;
					case SDLK_A:
						plane.velX = 0;
						break;
					}

			}

			
		}

		// Tick, every second
		currentTime = SDL_GetTicks();
		
		if (currentTime > lastTickTime + 1000) {

			// Logic
			plane.Tick();
			// Update bullets
			for (int i = plane.Bullets.size() - 1; i >= 0; i--) {
				plane.Bullets[i].Tick();

				if (!plane.Bullets[i].CheckBounds()) {
					plane.Bullets.erase(plane.Bullets.begin() + i);
				}
			}

			// Rendering

			// Set backround color
			SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);

			// Clear screen
			SDL_RenderClear(renderer);

			// Render plane
			plane.Render(renderer);

			// Render bullets
			for (int i = 0; i < plane.Bullets.size(); i++) {
				plane.Bullets[i].Render(renderer);
			}

			// Enviro
			DrawEnviro();

			// Draw onscreen
			SDL_RenderPresent(renderer);


		}

		

	}


	// Shutdown
	SDL_DestroyTexture(plane.texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return SDL_APP_SUCCESS;
}
