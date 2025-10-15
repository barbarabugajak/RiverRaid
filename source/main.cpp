#define SDL_MAIN_USE_CALLBACKS 1  // use the callbacks instead of main()
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>

// Create a variable for SDL window
SDL_Window* window = NULL;
// Create a variable for SDL renderer
SDL_Renderer * renderer = NULL;

// Initialize subsystems & variables used
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
	// Initalize video
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "Video did not initialize properly" << "\n";
		return SDL_APP_FAILURE;
	}
	else {
		std::cout << "Video initialized" << "\n";
	};

	// Initalize window & renderer
	if (!SDL_CreateWindowAndRenderer("Game", 720, 1280, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
		std::cout << "Window and renderer creation falied" << "\n";
		return SDL_APP_FAILURE;
	}
	else {
		std::cout << "Window and renderer created" << "\n";
	}

	return SDL_APP_CONTINUE;
}

// Handle events
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS; // Terminate successfully if quit
	}
	return SDL_APP_CONTINUE;
}

float red = 0.1f, green = 0.5f, blue = 0.8f, alpha = 1.0f;

// Game loop (Unreal's Tick(), Unity's Update())
SDL_AppResult SDL_AppIterate(void* appstate) {

	// Set backround color
	SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

	// Clear screen
	SDL_RenderClear(renderer);

	// Draw onscreen
	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE;

}

// This will fire once, on shutdown
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
	// Automatic cleanup of the renderer and window
}