// SDL
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_render.h>
#include "../libs/SDL3_image-3.2.4/include/SDL3_image/SDL_image.h"
#include <SDL3/SDL_keycode.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_ttf/SDL_textengine.h>
// Miniaudio
#include "../libs/miniaudio/miniaudio.h"
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

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
	ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;

	ma_uint64 framesRead = 0;
	ma_result result = ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, &framesRead); 

	// If fewer frames were read than requested
	if (framesRead < frameCount) {
		// Reset to beginning of the file 
		ma_decoder_seek_to_pcm_frame(pDecoder, 0);

		// Fill the remaning empty space in the buffer
		ma_uint64 extraFramesRead = 0;
		ma_decoder_read_pcm_frames(pDecoder, 
			(void*)((ma_uint64)(pOutput) + framesRead * pDecoder->outputChannels),  // To prevent overwriting
			frameCount - framesRead,
			&extraFramesRead);
	}
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
		std::cout << "Text initialized" << "\n";
	};

	SetupWindowAndRenderer();

	assert(window);
	assert(renderer);

	LoadFont();

	// Miniaudio
	ma_device_config config = ma_device_config_init(ma_device_type_playback);
	ma_decoder pDecoder;

	config.playback.format = ma_format_s16;
	config.playback.channels = 2;
	config.sampleRate = 48000;
	config.dataCallback = data_callback;
	config.pUserData = &pDecoder;

	ma_device device;
	if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {
		std::cout << "\n Audio device initialization failed \n";
		return -1;
	}

	const char* BACKGROUND_MUSIC_ASSET_PATH = "assets/audio/game-8-bit.wav";
	ma_result fileResult = ma_decoder_init_file(BACKGROUND_MUSIC_ASSET_PATH, NULL, &pDecoder);
	if (fileResult != MA_SUCCESS) {
		std::cout << "\n Wav import errors: " << fileResult << "\n";
		return -1;
	}

	ma_data_source_set_looping(&pDecoder, MA_TRUE);

	ma_device_start(&device);

	float red = 0.0f, green = 0.1f, blue = 0.7f, alpha = 1.0f;
	PrepareEnviro();

	GameplayHandler gameplayHandler;
	gameplayHandler.Init();;

	Uint64 last = SDL_GetPerformanceCounter();
	float accumulator = 0;
	Uint64 startTime = SDL_GetTicks();
	int frameCount = 0;

	SDL_ShowCursor();
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
				if (event.key.key == SDLK_ESCAPE && !gameplayHandler.bGameOver) {

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
	ma_device_uninit(&device);
	ma_decoder_uninit(&pDecoder);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return SDL_APP_SUCCESS;
}
