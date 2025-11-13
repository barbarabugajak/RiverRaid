#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/GameObject.h"
#include <iostream>
#include <cassert>


	class AnimatedObject : public GameObject {

	public:
		const char* name = nullptr;
		std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture;
		float velX = 0.f;
		float velY = 0.f;
		float speedX = 0.f;
		float speedY = 0.f;
		int frameAmount = 0;

		using GameObject::GameObject;

		void Render(SDL_Renderer* renderer);
	
		// Happens every game loop
		virtual void Tick(float dt) {

		};

	};