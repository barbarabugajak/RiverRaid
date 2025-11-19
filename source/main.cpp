// SDL
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_ttf/SDL_textengine.h>
// Project headers
#include "../source/textures.h"
#include "../source/gameObject.h"
#include "../source/enviro.h"
#include "../source/globals.h"
#include "../source/bullet.h"
#include "../source/plane.h"
#include "../source/enemy.h"
#include "../source/gameplayHandler.h"
#include "../source/button.h"
#include "../source/textObject.h"
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
	
	// Initialize SDL text library
	if (!TTF_Init()) {
		std::cout << "Text did not initialize properly" << "\n";
		std::cout << SDL_GetError() << "\n";
		return SDL_APP_FAILURE;
	}
	else {
		std::cout << "Text initialized" << "\n";
	};

	SetupWindowAndRenderer();

	assert(window);
	assert(renderer);

	LoadFont();

	float red = 0.0f, green = 0.1f, blue = 0.7f, alpha = 1.0f;
	PrepareEnviro();

	GameplayHandler gameplayHandler;
	gameplayHandler.Init();;

	Uint64 last = SDL_GetPerformanceCounter();
	float accumulator = 0;
	Uint64 startTime = SDL_GetTicks();
	int frameCount = 0;

	
	SDL_ShowCursor();
	// Game loop
	while (!bShouldQuit) {

		SDL_Event event;

		// Event pump
		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_EVENT_QUIT) {
				bShouldQuit = true;
				break;
			}

			if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				gameplayHandler.CheckIfAnyButtonWasClicked();
				break;
			}

			if (event.type == SDL_EVENT_KEY_DOWN) {
				if (event.key.key == SDLK_ESCAPE) {

					bIsPaused = !bIsPaused;
					gameplayHandler.bShowUI = !gameplayHandler.bShowUI;
					if (bIsPaused) {
						SDL_ShowCursor();
					}
					else {
						SDL_HideCursor();
					}
				}
			}
		}		
		
			Uint64 now = SDL_GetPerformanceCounter();
			float diff = (float)(now - last) / SDL_GetPerformanceFrequency();
			last = now;
			accumulator += diff;
		

		while (accumulator >= TARGET_FRAME_TIME) {

			if (!bIsPaused) {
				// ============= Logic ==============
				gameplayHandler.Tick(TARGET_FRAME_TIME);
			}


			// ========== Rendering =============
			SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);
			SDL_RenderClear(renderer);
			gameplayHandler.Render();
			SDL_SetRenderDrawColorFloat(renderer, green, blue, blue, SDL_ALPHA_OPAQUE_FLOAT);
			SDL_RenderPresent(renderer);


			// ========== Frame Rate =============
			accumulator -= TARGET_FRAME_TIME;
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
