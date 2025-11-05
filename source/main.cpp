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
#include "../source/enemy.h"
#include "../source/gameState.h"

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

	SetupWindowAndRenderer();


	// Declare variables for window and renderer
	assert(window);
	assert(renderer);
	
	Plane plane("plane", "source/assets/plane.png", renderer, 0, 0, 100, 100, 540.f, 50.f);

	plane.velX = 0;
	plane.sprite.x = (WIDTH / 2) - (plane.sprite.w / 2);
	plane.sprite.y = HEIGHT - 200;

	bool close = false;
	float red = 0.0f, green = 0.1f, blue = 0.7f, alpha = 1.0f;

	// Initialize enviro
	PrepareEnviro();

	// Tick handlers
	Uint64 last = SDL_GetPerformanceCounter();
	const float targetFrameTime = 1.0f / 60.0f;
	float accumulator = 0;

	// FPS counters
	Uint64 startTime = SDL_GetTicks();
	int frameCount = 0;

	// Game loop
	while (!close) {

		SDL_Event event;

		// Event pump
		while (SDL_PollEvent(&event)) {

			// Quit event handler
			if (event.type == SDL_EVENT_QUIT) {
				close = true;
				break;
			}
		}		

		// Frame-rate controllers
		Uint64 now = SDL_GetPerformanceCounter();
		float diff = (float)(now - last) / SDL_GetPerformanceFrequency();
		last = now;
		accumulator += diff;

		// Temporary here for tests
		// Enemy enemy("enemy", "source/assets/helicopter.png", renderer, 200, 300, 100, 75, 30, 0);
		
		while (accumulator >= targetFrameTime) {

			// Logic
			plane.Tick(targetFrameTime);
			for (int i = (int)plane.Bullets.size() - 1; i >= 0; i--) { 

				plane.Bullets[i].Tick(targetFrameTime);

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

			// Render enemies
			// enemy.Render(renderer);

			// Render bullets
			for (int i = 0; i < plane.Bullets.size(); i++) {
				plane.Bullets[i].Render(renderer);
			}

			// Enviro
			DrawEnviro();

			// Draw onscreen
			SDL_RenderPresent(renderer);

			accumulator -= targetFrameTime;

			Uint64 currentTime = SDL_GetTicks();
			float elapsedTime = (currentTime - startTime) / 1000.0f;
			frameCount++;

			if (elapsedTime >= 1.0f) {
				float fps = frameCount / elapsedTime;
				std::cout << "FPS: " << fps << "\n";

				frameCount = 0;
				startTime = currentTime;
			}
		}

		
		
	}

	// Shutdown
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return SDL_APP_SUCCESS;
}
