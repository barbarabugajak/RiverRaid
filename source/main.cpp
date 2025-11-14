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

void unPause() {
	std::cout << "OnClick fired";
	bIsPaused = false;
}

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
		std::cout << "Video initialized" << "\n";
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

	// Temporary here for tests
	Button startGameButton((WIDTH - 200.0f) / 2, HEIGHT / 2.f, 200.f, 60.f, unPause, 0.f, 1.f, 0.1f);
	
	TextObject<int> score("Score: %d", WIDTH / 2.f, HEIGHT - 100, 150.0f, 50.f, 255, 255, 255, gameplayHandler.score);
	score.sprite.x = (WIDTH - score.sprite.w) / 2;
	const char* emptyString = "";
	// TextObject<const char*> msg("Message: %s", 200.f, HEIGHT / 4.f, 200.f, 50.f, 255, 0, 255, emptyString);
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
				startGameButton.CheckHover();
				break;
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
			startGameButton.Render();
			score.Render();
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
