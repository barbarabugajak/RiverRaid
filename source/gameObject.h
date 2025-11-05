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
	SDL_Texture* texture = nullptr;
	float velX = 0.f;
	float velY = 0.f;
	float speedX = 0.f;
	float speedY = 0.f;

	GameObject(
		const char* objectName,
		const char* path_to_texture,
		SDL_Renderer* renderer,
		float x, float y, float w, float h, float speedValX, float speedValY) :

			texture(CreateTextureFromPNG(path_to_texture, renderer)),
			name(objectName),
			sprite({x, y, w, h}),
			speedX(speedValX),
			speedY(speedValY),
			velX(0.f),
			velY(0.f)
	{};

	
	GameObject(GameObject&& Other) noexcept :
		texture(Other.texture),
		name(Other.name),
		speedX(Other.speedX),
		speedY(Other.speedY),
		velX(Other.velX),
		velY(Other.velY),
		sprite(Other.sprite)
	{
		Other.texture = nullptr;
	}
	

	~GameObject() {
		if (texture)
		{
 			SDL_DestroyTexture(texture);
		}
	}

	
	GameObject& operator=(const GameObject& Other) = delete;
	GameObject& operator=(GameObject&& Other) noexcept 
	{
		if (texture)
		{
			SDL_DestroyTexture(texture);
		}
		texture = Other.texture;
		name = Other.name;
		speedX = Other.speedX;
		speedY = Other.speedY;
		sprite = Other.sprite;
		velX = Other.velX;
		velY = Other.velY;
		Other.texture = nullptr;

		return *this;
	}

	// Happens every game loop
	virtual void Tick(float dt) {

	}

	const void Render(SDL_Renderer* renderer) {

		SDL_RenderTexture(renderer, texture, NULL, &sprite);
	}
};



std::ostream& operator<<(std::ostream& os, const GameObject& gO)
{
	os << gO.name << " at : (" << gO.sprite.x << "; " << gO.sprite.y << ") " << gO.sprite.h << " x " << gO.sprite.w << "\n";
	return os;
}