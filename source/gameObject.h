#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include <iostream>

class GameObject {

public:
	const char* name;
	SDL_FRect* rectangle;
	SDL_Texture* texture;
	int speedX;

	GameObject(
		const char* objectName,
		const char* path_to_texture,
		SDL_Renderer* renderer,
		float x, float y, float w, float h, int speedVal) {

		name = objectName;

		rectangle = new SDL_FRect();

		rectangle->x = x;
		rectangle->y = y;
		rectangle->w = w;
		rectangle->h = h;

		speedX = speedVal;

		texture = CreateTextureFromPNG(path_to_texture, renderer);

		if (!texture) {
			std::cout << SDL_GetError() << "\n";
		}
	};

	void MoveX(int value) {
		rectangle->x += value*speedX;
	}
};



std::ostream& operator<<(std::ostream& os, const GameObject& gO)
{
	os << gO.name << " at : (" << gO.rectangle->x << "; " << gO.rectangle->x << ") " << gO.rectangle->w << " x " << gO.rectangle->w << "\n";
	return os;
}