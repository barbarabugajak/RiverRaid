#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/gameObject.h"
#include <iostream>
#include <cassert>


GameObject::GameObject(
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


void GameObject::Render(SDL_Renderer* renderer) {
	SDL_RenderTexture(renderer, texture.get(), NULL, &sprite);
}

void GameObject::MoveY(float value) {
	sprite.y += value;
}



std::ostream& operator<<(std::ostream& os, const GameObject& gO)
{
	os << gO.name << " at : (" << gO.sprite.x << "; " << gO.sprite.y << ") " << gO.sprite.h << " x " << gO.sprite.w << "\n";
	return os;
}
