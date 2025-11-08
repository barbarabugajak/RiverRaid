	#pragma once
	#include <SDL3/SDL_rect.h>
	#include <SDL3/SDL_render.h>
	#include "../source/textures.h"
	#include "../source/globals.h"
	#include <iostream>
	#include <cassert>


	class GameObject {

	public:
		const char* name = nullptr;
		SDL_FRect sprite;
		std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture;
		float velX = 0.f;
		float velY = 0.f;
		float speedX = 0.f;
		float speedY = 0.f;

		GameObject(
			const char* objectName,
			const char* path_to_texture,
			SDL_Renderer* renderer,
			float x, float y, float w, float h, float speedValX, float speedValY
		);


		void Render(SDL_Renderer* renderer);

		void MoveY(float value);
	
		// Happens every game loop
		virtual void Tick(float dt) {

		};

	};