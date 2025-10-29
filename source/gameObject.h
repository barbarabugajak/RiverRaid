#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/globals.h"
#include <iostream>
#include <cassert>


class GameObject {

public:
	const char* name;
	SDL_FRect* sprite;
	SDL_Texture* texture;
	float velX = 0;
	float velY = 0;
	int speedX;
	int speedY;

	GameObject(
		const char* objectName,
		const char* path_to_texture,
		SDL_Renderer* renderer,
		float x, float y, float w, float h, int speedValX, int speedValY) {

		name = objectName;

		sprite = new SDL_FRect();

		sprite->x = x;
		sprite->y = y;
		sprite->w = w;
		sprite->h = h;

		speedX = speedValX;
		velX = speedX;

		speedY = speedValY;
		velY = speedY;

		texture = CreateTextureFromPNG(path_to_texture, renderer);
		
	};

	const void Render(SDL_Renderer* renderer) {

		SDL_RenderTexture(renderer, texture, NULL, sprite);
	}

	const void Destroy() {
		SDL_DestroyTexture(texture);
	}

	// Happens every game loop
	virtual void Tick() {

	}
};



std::ostream& operator<<(std::ostream& os, const GameObject& gO)
{
	os << gO.name << " at : (" << gO.sprite->x << "; " << gO.sprite->x << ") " << gO.sprite->w << " x " << gO.sprite->w << "\n";
	return os;
}