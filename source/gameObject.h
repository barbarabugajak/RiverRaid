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
		float x, float y, float w, float h, float speedValX, float speedValY) : 

		texture(CreateTextureFromPNG(path_to_texture, renderer), [](SDL_Texture* t) { if (t) SDL_DestroyTexture(t); })

		{

		name = objectName;

		sprite = SDL_FRect{ x,y,w,h };

		speedX = speedValX;
		velX = speedX;

		speedY = speedValY;
		velY = speedY;

	};

	const void Render(SDL_Renderer* renderer) {

		SDL_RenderTexture(renderer, texture.get(), NULL, &sprite);
	}

	// Happens every game loop
	virtual void Tick(float dt) {

	}

};



std::ostream& operator<<(std::ostream& os, const GameObject& gO)
{
	os << gO.name << " at : (" << gO.sprite.x << "; " << gO.sprite.y << ") " << gO.sprite.h << " x " << gO.sprite.w << "\n";
	return os;
}